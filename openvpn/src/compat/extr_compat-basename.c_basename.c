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
 char* strrchr (char*,char) ; 

char *
basename(char *filename)
{
    char *p = strrchr(filename, '/');
    if (!p)
    {
        /* If NULL, check for \ instead ... might be Windows a path */
        p = strrchr(filename, '\\');
    }
    return p ? p + 1 : (char *) filename;
}