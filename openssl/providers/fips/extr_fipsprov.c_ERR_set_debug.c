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
 int /*<<< orphan*/  c_set_error_debug (int /*<<< orphan*/ *,char const*,int,char const*) ; 

void ERR_set_debug(const char *file, int line, const char *func)
{
    c_set_error_debug(NULL, file, line, func);
}