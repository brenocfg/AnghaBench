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
 scalar_t__ UNLIKELY (int) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static char *
strsep_char(char *strp, const char *end, char delim)
{
    char *ptr;

    if (UNLIKELY(!strp))
        return NULL;

    if (UNLIKELY(strp > end))
        return NULL;

    ptr = strchr(strp, delim);
    if (UNLIKELY(!ptr))
        return NULL;

    *ptr = '\0';
    return ptr + 1;
}