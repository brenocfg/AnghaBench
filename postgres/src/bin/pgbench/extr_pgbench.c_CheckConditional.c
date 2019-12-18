#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; int meta; } ;
struct TYPE_4__ {int /*<<< orphan*/  desc; TYPE_2__** commands; } ;
typedef  TYPE_1__ ParsedScript ;
typedef  int /*<<< orphan*/  ConditionalStack ;
typedef  TYPE_2__ Command ;

/* Variables and functions */
 int /*<<< orphan*/  ConditionError (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  IFSTATE_ELSE_FALSE ; 
 int /*<<< orphan*/  IFSTATE_FALSE ; 
 scalar_t__ META_COMMAND ; 
#define  META_ELIF 131 
#define  META_ELSE 130 
#define  META_ENDIF 129 
#define  META_IF 128 
 int /*<<< orphan*/  conditional_stack_create () ; 
 int /*<<< orphan*/  conditional_stack_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ conditional_stack_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conditional_stack_peek (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conditional_stack_poke (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conditional_stack_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conditional_stack_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CheckConditional(ParsedScript ps)
{
	/* statically check conditional structure */
	ConditionalStack cs = conditional_stack_create();
	int			i;

	for (i = 0; ps.commands[i] != NULL; i++)
	{
		Command    *cmd = ps.commands[i];

		if (cmd->type == META_COMMAND)
		{
			switch (cmd->meta)
			{
				case META_IF:
					conditional_stack_push(cs, IFSTATE_FALSE);
					break;
				case META_ELIF:
					if (conditional_stack_empty(cs))
						ConditionError(ps.desc, i + 1, "\\elif without matching \\if");
					if (conditional_stack_peek(cs) == IFSTATE_ELSE_FALSE)
						ConditionError(ps.desc, i + 1, "\\elif after \\else");
					break;
				case META_ELSE:
					if (conditional_stack_empty(cs))
						ConditionError(ps.desc, i + 1, "\\else without matching \\if");
					if (conditional_stack_peek(cs) == IFSTATE_ELSE_FALSE)
						ConditionError(ps.desc, i + 1, "\\else after \\else");
					conditional_stack_poke(cs, IFSTATE_ELSE_FALSE);
					break;
				case META_ENDIF:
					if (!conditional_stack_pop(cs))
						ConditionError(ps.desc, i + 1, "\\endif without matching \\if");
					break;
				default:
					/* ignore anything else... */
					break;
			}
		}
	}
	if (!conditional_stack_empty(cs))
		ConditionError(ps.desc, i + 1, "\\if without matching \\endif");
	conditional_stack_destroy(cs);
}