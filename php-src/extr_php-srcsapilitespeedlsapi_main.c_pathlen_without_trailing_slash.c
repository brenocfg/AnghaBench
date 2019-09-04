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
 char DEFAULT_SLASH ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int pathlen_without_trailing_slash(char *path)
{
    int len = (int)strlen(path);
    while (len > 1 && /* mind "/" as root dir */
           path[len-1] == DEFAULT_SLASH)
    {
        --len;
    }
    return len;
}