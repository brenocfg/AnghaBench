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
 int /*<<< orphan*/  mp_isdigit (char const) ; 

__attribute__((used)) static bool all_digits(const char *str)
{
    if (str == NULL || str[0] == '\0') {
        return false;
    }

    for (const char *c = str; *c != '\0'; ++c) {
        if (!mp_isdigit(*c))
            return false;
    }
    return true;
}