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
 scalar_t__ strcmp (char const* const,char const*) ; 

__attribute__((used)) static void set_next_str(const char * const *list, const char **str,
                         const char **msg)
{
    int ind;
    for (ind = 0; list[ind]; ind += 2) {
        if (strcmp(list[ind], *str) == 0) {
            if (list[ind + 2] == NULL)
                ind = -2;
            *str = list[ind + 2];
            *msg = list[ind + 3];
            return;
        }
    }

    *str = list[0];
    *msg = list[1];
}