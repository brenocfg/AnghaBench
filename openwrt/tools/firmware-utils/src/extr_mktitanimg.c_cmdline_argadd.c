#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* p_next; } ;
struct TYPE_5__ {scalar_t__ argc; TYPE_2__* list; } ;
typedef  TYPE_1__ CMDLINE_ARGS ;
typedef  TYPE_2__ CMDLINE_ARG ;

/* Variables and functions */

__attribute__((used)) static void cmdline_argadd(CMDLINE_ARGS* p_arglist, CMDLINE_ARG* p_arg)
{
	CMDLINE_ARG*	p_list;
	CMDLINE_ARG*	p_prev=NULL;

	/* See if we had anything in the list */
	if(p_arglist->argc == 0)
	{
		/* Link the argument in */
		p_arglist->list = p_arg;
	}
	else
	{
		/* Find the tail of the list */
		for(p_list=p_arglist->list; p_list != NULL; p_list=p_list->p_next)
			p_prev = p_list;

		/* Link the argument in */
		p_prev->p_next=p_arg;
	}

	/* Keep track of arg number */
	p_arglist->argc++;
}