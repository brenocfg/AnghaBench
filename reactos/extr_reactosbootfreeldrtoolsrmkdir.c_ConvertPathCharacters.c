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
 char DOS_PATH_CHAR ; 
 char PATH_CHAR ; 
 char UNIX_PATH_CHAR ; 

void ConvertPathCharacters(char *Path)
{
    int        i;

    i = 0;
    while (Path[i] != 0)
    {
        if (Path[i] == DOS_PATH_CHAR || Path[i] == UNIX_PATH_CHAR)
        {
            Path[i] = PATH_CHAR;
        }

        i++;
    }
}