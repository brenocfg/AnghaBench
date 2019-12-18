#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  chdir (char*) ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 scalar_t__ mkdir (char*,...) ; 
 int /*<<< orphan*/  perror (char*) ; 

int MakeDirectory(char *Directory)
{
    char    CurrentDirectory[1024];

    getcwd(CurrentDirectory, 1024);

    if (chdir(Directory) == 0)
    {
        chdir(CurrentDirectory);
        return 0;
    }

#if defined (UNIX_PATHS) || defined (__DJGPP__)
    if (mkdir(Directory, 0755) != 0)
    {
        perror("Failed to create directory");
        return 1;
    }
#else
    if (mkdir(Directory) != 0)
    {
        perror("Failed to create directory");
        return 1;
    }
#endif

    if (chdir(Directory) != 0)
    {
        perror("Failed to change directory");
        return 1;
    }

    chdir(CurrentDirectory);

    return 0;
}