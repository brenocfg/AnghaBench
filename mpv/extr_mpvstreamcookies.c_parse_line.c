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

__attribute__((used)) static int parse_line(char **ptr, char *cols[7])
{
    int col;
    cols[0] = *ptr;

    for (col = 1; col < 7; col++) {
        for (; (**ptr) > 31; (*ptr)++);
        if (**ptr == 0)
            return 0;
        (*ptr)++;
        if ((*ptr)[-1] != 9)
            return 0;
        cols[col] = (*ptr);
    }

    return 1;
}