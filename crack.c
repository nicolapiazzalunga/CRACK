// Simple brute force password cracking program

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <crypt.h>

int main(int argc, string argv[])
{
    // Check input validity
    if (argc != 2 || strlen(argv[1]) < 13)
    {
        printf("Usage: ./crack hashed_password\n");
        return 1;
    }

    // Stores original hash and "salt"
    char hash[strlen(argv[1])];
    strcpy(hash, argv[1]);
    char salt[3];
    for (int i = 0; i < 2; i++)
    {
        salt[i] = hash[i];
    }
    salt[2] = '\0';

    // Guess a password until MAXCHARACTERS
    // Iterates a character from 'a' to 'Z'
    const int MAXCHARACTERS = 5;        // Max password length
    int pwlen = 0;                      // Password length
    while (pwlen < MAXCHARACTERS)
    {
        // Initialize password guess
        char my_guess[pwlen + 1];
        for (int j = 0; j < pwlen + 1; j++)
        {
            my_guess[j] = 'A' - 1;
        }

        // Main recursion
        int p = 0;
        bool condition = true;
        while (condition)
        {
            if (my_guess[p] < 'z')
            {
                // Selects only alphabetical charachters
                int z = 1;
                while (!isalpha(my_guess[p] + z))
                {
                    z++;
                }
                my_guess[p] = my_guess[p] + z;

                // Hashes the guess
                char my_hash[strlen(hash)];
                strcpy(my_hash, crypt(my_guess, salt));

                // Compares the original and the guessed hash. If found, print pw and exit
                if (!strcmp(my_hash, hash))
                {
                    printf("%s\n", my_guess);
                    return 0;
                }

                // If guess is wrong, if available, iterate in next position otherwise iterate in current position
                if (p < pwlen)
                {
                    p = p + 1;
                }
            }
            else
            {
                // If left-most digit and all the right digits have been iterated then fail and maxcharacters reached
                if (p == 0 && pwlen == MAXCHARACTERS - 1)
                {
                    printf("Fail! \n");
                    return 1;
                }
                // If left-most digit and all the right digits have been iterated then fail but maxcharacters NOT reached
                else if (p == 0)
                {
                    condition = false;
                }
                // Else, repeat iteration changing the digit on the right
                else
                {
                    my_guess[p] = 'A';
                    p = p - 1;
                }
            }

        }

        // Increase password length
        pwlen++;
    }
}
