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
struct debug_variable {int* ptr; scalar_t__ name; } ;

/* Variables and functions */
 struct debug_variable* debug_variables ; 

int perf_quiet_option(void)
{
	struct debug_variable *var = &debug_variables[0];

	/* disable all debug messages */
	while (var->name) {
		*var->ptr = -1;
		var++;
	}

	return 0;
}