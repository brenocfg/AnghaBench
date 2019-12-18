#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * opt_args; } ;

/* Variables and functions */
 TYPE_1__ cmdline_data ; 

void* cmdline_getarg_list(char opt)
{
	int index = (opt - 'a');

	/* Check the validity of the index */
	if((index < 0) || (index > 25))
	{
		/* ERROR: Wrong option */
		return NULL;
	}

	/* Return a pointer to the ARGS control structure */
	return((void*)(&cmdline_data.opt_args[index]));
}