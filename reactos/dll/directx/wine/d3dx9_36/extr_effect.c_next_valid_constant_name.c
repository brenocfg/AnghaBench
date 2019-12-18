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
 scalar_t__ isalpha (char) ; 
 scalar_t__ isdigit (char) ; 

__attribute__((used)) static char *next_valid_constant_name(char **string)
{
    char *ret = *string;
    char *next;

    while (*ret && !isalpha(*ret) && *ret != '_')
        ++ret;
    if (!*ret)
        return NULL;

    next = ret + 1;
    while (isalpha(*next) || isdigit(*next) || *next == '_')
        ++next;
    if (*next)
        *next++ = 0;
    *string = next;
    return ret;
}