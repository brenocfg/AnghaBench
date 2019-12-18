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
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void unfold_header(char *header, int len)
{
    char *start = header, *cp = header;

    do {
        while(*cp == ' ' || *cp == '\t')
        {
            cp++;
            len--;
        }
        if(cp != start)
            memmove(start, cp, len + 1);

        cp = strstr(start, "\r\n");
        len -= (cp - start);
        start = cp;
        *start = ' ';
        start++;
        len--;
        cp += 2;
    } while(*cp == ' ' || *cp == '\t');

    *(start - 1) = '\0';
}