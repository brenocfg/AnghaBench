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
 unsigned long get_error_values (int /*<<< orphan*/ ,int,char const**,int*,char const**,int*) ; 

unsigned long ERR_peek_last_error_line_data(const char **file, int *line,
                                            const char **data, int *flags)
{
    return get_error_values(0, 1, file, line, data, flags);
}