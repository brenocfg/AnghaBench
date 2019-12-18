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
 scalar_t__ l_isspace (char) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static const char *strip(char *str)
{
    size_t length;
    char *result = str;
    while (*result && l_isspace(*result))
        result++;

    length = strlen(result);
    if (length == 0)
        return result;

    while (l_isspace(result[length - 1]))
        result[--length] = '\0';

    return result;
}