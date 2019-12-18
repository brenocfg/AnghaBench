#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int p_next_resno; int p_resolve_unknowns; int /*<<< orphan*/  p_queryEnv; int /*<<< orphan*/  p_ref_hook_state; int /*<<< orphan*/  p_coerce_param_hook; int /*<<< orphan*/  p_paramref_hook; int /*<<< orphan*/  p_post_columnref_hook; int /*<<< orphan*/  p_pre_columnref_hook; int /*<<< orphan*/  p_sourcetext; struct TYPE_5__* parentParseState; } ;
typedef  TYPE_1__ ParseState ;

/* Variables and functions */
 TYPE_1__* palloc0 (int) ; 

ParseState *
make_parsestate(ParseState *parentParseState)
{
	ParseState *pstate;

	pstate = palloc0(sizeof(ParseState));

	pstate->parentParseState = parentParseState;

	/* Fill in fields that don't start at null/false/zero */
	pstate->p_next_resno = 1;
	pstate->p_resolve_unknowns = true;

	if (parentParseState)
	{
		pstate->p_sourcetext = parentParseState->p_sourcetext;
		/* all hooks are copied from parent */
		pstate->p_pre_columnref_hook = parentParseState->p_pre_columnref_hook;
		pstate->p_post_columnref_hook = parentParseState->p_post_columnref_hook;
		pstate->p_paramref_hook = parentParseState->p_paramref_hook;
		pstate->p_coerce_param_hook = parentParseState->p_coerce_param_hook;
		pstate->p_ref_hook_state = parentParseState->p_ref_hook_state;
		/* query environment stays in context for the whole parse analysis */
		pstate->p_queryEnv = parentParseState->p_queryEnv;
	}

	return pstate;
}