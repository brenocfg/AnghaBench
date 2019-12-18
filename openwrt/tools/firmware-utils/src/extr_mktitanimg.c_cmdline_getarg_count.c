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
struct TYPE_2__ {int argc; } ;
typedef  TYPE_1__ CMDLINE_ARGS ;

/* Variables and functions */

int cmdline_getarg_count(void* list)
{
	CMDLINE_ARGS*	p_args = (CMDLINE_ARGS*)list;

	/* Return number of arguments for this option */
	return(p_args->argc);
}