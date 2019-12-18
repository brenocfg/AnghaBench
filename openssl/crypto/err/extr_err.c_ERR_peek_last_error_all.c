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
 int /*<<< orphan*/  EV_PEEK_LAST ; 
 unsigned long get_error_values (int /*<<< orphan*/ ,char const**,int*,char const**,char const**,int*) ; 

unsigned long ERR_peek_last_error_all(const char **file, int *line,
                                      const char **func,
                                      const char **data, int *flags)
{
    return get_error_values(EV_PEEK_LAST, file, line, func, data, flags);
}