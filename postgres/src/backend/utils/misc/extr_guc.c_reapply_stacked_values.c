#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  reset_source; int /*<<< orphan*/  reset_scontext; } ;
struct config_string {char const* reset_val; TYPE_5__ gen; } ;
struct config_generic {char* name; TYPE_6__* stack; } ;
struct TYPE_10__ {char const* stringval; } ;
struct TYPE_11__ {TYPE_3__ val; } ;
struct TYPE_8__ {char* stringval; } ;
struct TYPE_9__ {TYPE_1__ val; } ;
struct TYPE_13__ {int state; int /*<<< orphan*/  nest_level; int /*<<< orphan*/  masked_scontext; TYPE_4__ masked; int /*<<< orphan*/  source; int /*<<< orphan*/  scontext; TYPE_2__ prior; struct TYPE_13__* prev; } ;
typedef  TYPE_6__ GucStack ;
typedef  int /*<<< orphan*/  GucSource ;
typedef  int /*<<< orphan*/  GucContext ;

/* Variables and functions */
 int /*<<< orphan*/  GUC_ACTION_LOCAL ; 
 int /*<<< orphan*/  GUC_ACTION_SAVE ; 
 int /*<<< orphan*/  GUC_ACTION_SET ; 
#define  GUC_LOCAL 131 
#define  GUC_SAVE 130 
#define  GUC_SET 129 
#define  GUC_SET_LOCAL 128 
 int /*<<< orphan*/  PGC_S_SESSION ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  set_config_option (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
reapply_stacked_values(struct config_generic *variable,
					   struct config_string *pHolder,
					   GucStack *stack,
					   const char *curvalue,
					   GucContext curscontext, GucSource cursource)
{
	const char *name = variable->name;
	GucStack   *oldvarstack = variable->stack;

	if (stack != NULL)
	{
		/* First, recurse, so that stack items are processed bottom to top */
		reapply_stacked_values(variable, pHolder, stack->prev,
							   stack->prior.val.stringval,
							   stack->scontext, stack->source);

		/* See how to apply the passed-in value */
		switch (stack->state)
		{
			case GUC_SAVE:
				(void) set_config_option(name, curvalue,
										 curscontext, cursource,
										 GUC_ACTION_SAVE, true,
										 WARNING, false);
				break;

			case GUC_SET:
				(void) set_config_option(name, curvalue,
										 curscontext, cursource,
										 GUC_ACTION_SET, true,
										 WARNING, false);
				break;

			case GUC_LOCAL:
				(void) set_config_option(name, curvalue,
										 curscontext, cursource,
										 GUC_ACTION_LOCAL, true,
										 WARNING, false);
				break;

			case GUC_SET_LOCAL:
				/* first, apply the masked value as SET */
				(void) set_config_option(name, stack->masked.val.stringval,
										 stack->masked_scontext, PGC_S_SESSION,
										 GUC_ACTION_SET, true,
										 WARNING, false);
				/* then apply the current value as LOCAL */
				(void) set_config_option(name, curvalue,
										 curscontext, cursource,
										 GUC_ACTION_LOCAL, true,
										 WARNING, false);
				break;
		}

		/* If we successfully made a stack entry, adjust its nest level */
		if (variable->stack != oldvarstack)
			variable->stack->nest_level = stack->nest_level;
	}
	else
	{
		/*
		 * We are at the end of the stack.  If the active/previous value is
		 * different from the reset value, it must represent a previously
		 * committed session value.  Apply it, and then drop the stack entry
		 * that set_config_option will have created under the impression that
		 * this is to be just a transactional assignment.  (We leak the stack
		 * entry.)
		 */
		if (curvalue != pHolder->reset_val ||
			curscontext != pHolder->gen.reset_scontext ||
			cursource != pHolder->gen.reset_source)
		{
			(void) set_config_option(name, curvalue,
									 curscontext, cursource,
									 GUC_ACTION_SET, true, WARNING, false);
			variable->stack = NULL;
		}
	}
}