#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int index; struct TYPE_4__* p_next; } ;
struct TYPE_3__ {int argc; TYPE_2__* list; } ;
typedef  TYPE_1__ CMDLINE_ARGS ;
typedef  TYPE_2__ CMDLINE_ARG ;

/* Variables and functions */

int cmdline_getarg(void* list, int num)
{
	int i;
	CMDLINE_ARGS*	p_args = (CMDLINE_ARGS*)list;
	CMDLINE_ARG*	p_arg;

	/* Search the 'num' argument in the list for this option */
	for(i=0,p_arg=p_args->list; (p_arg!=NULL) && (i<p_args->argc); i++, p_arg=p_arg->p_next)
	{
		/* if num matches i, we found it */
		if(i==num) return(p_arg->index);
	}
	/* We did not find the specified argument or the list was empty */
	return -1;
}