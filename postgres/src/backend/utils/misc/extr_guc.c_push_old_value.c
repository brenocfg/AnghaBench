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
struct config_generic {TYPE_1__* stack; int /*<<< orphan*/  scontext; int /*<<< orphan*/  source; } ;
struct TYPE_2__ {scalar_t__ nest_level; void* state; int /*<<< orphan*/  prior; int /*<<< orphan*/  scontext; int /*<<< orphan*/  source; struct TYPE_2__* prev; int /*<<< orphan*/  masked; int /*<<< orphan*/  masked_scontext; } ;
typedef  TYPE_1__ GucStack ;
typedef  int GucAction ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ GUCNestLevel ; 
#define  GUC_ACTION_LOCAL 130 
#define  GUC_ACTION_SAVE 129 
#define  GUC_ACTION_SET 128 
 void* GUC_LOCAL ; 
 void* GUC_SAVE ; 
 void* GUC_SET ; 
 void* GUC_SET_LOCAL ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TopTransactionContext ; 
 int /*<<< orphan*/  discard_stack_value (struct config_generic*,int /*<<< orphan*/ *) ; 
 int guc_dirty ; 
 int /*<<< orphan*/  set_stack_value (struct config_generic*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
push_old_value(struct config_generic *gconf, GucAction action)
{
	GucStack   *stack;

	/* If we're not inside a nest level, do nothing */
	if (GUCNestLevel == 0)
		return;

	/* Do we already have a stack entry of the current nest level? */
	stack = gconf->stack;
	if (stack && stack->nest_level >= GUCNestLevel)
	{
		/* Yes, so adjust its state if necessary */
		Assert(stack->nest_level == GUCNestLevel);
		switch (action)
		{
			case GUC_ACTION_SET:
				/* SET overrides any prior action at same nest level */
				if (stack->state == GUC_SET_LOCAL)
				{
					/* must discard old masked value */
					discard_stack_value(gconf, &stack->masked);
				}
				stack->state = GUC_SET;
				break;
			case GUC_ACTION_LOCAL:
				if (stack->state == GUC_SET)
				{
					/* SET followed by SET LOCAL, remember SET's value */
					stack->masked_scontext = gconf->scontext;
					set_stack_value(gconf, &stack->masked);
					stack->state = GUC_SET_LOCAL;
				}
				/* in all other cases, no change to stack entry */
				break;
			case GUC_ACTION_SAVE:
				/* Could only have a prior SAVE of same variable */
				Assert(stack->state == GUC_SAVE);
				break;
		}
		Assert(guc_dirty);		/* must be set already */
		return;
	}

	/*
	 * Push a new stack entry
	 *
	 * We keep all the stack entries in TopTransactionContext for simplicity.
	 */
	stack = (GucStack *) MemoryContextAllocZero(TopTransactionContext,
												sizeof(GucStack));

	stack->prev = gconf->stack;
	stack->nest_level = GUCNestLevel;
	switch (action)
	{
		case GUC_ACTION_SET:
			stack->state = GUC_SET;
			break;
		case GUC_ACTION_LOCAL:
			stack->state = GUC_LOCAL;
			break;
		case GUC_ACTION_SAVE:
			stack->state = GUC_SAVE;
			break;
	}
	stack->source = gconf->source;
	stack->scontext = gconf->scontext;
	set_stack_value(gconf, &stack->prior);

	gconf->stack = stack;

	/* Ensure we remember to pop at end of xact */
	guc_dirty = true;
}