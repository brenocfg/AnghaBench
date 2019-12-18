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
struct ParseState {void* p_ref_hook_state; int /*<<< orphan*/  p_paramref_hook; int /*<<< orphan*/  p_post_columnref_hook; int /*<<< orphan*/  p_pre_columnref_hook; } ;
typedef  int /*<<< orphan*/  PLpgSQL_expr ;

/* Variables and functions */
 int /*<<< orphan*/  plpgsql_param_ref ; 
 int /*<<< orphan*/  plpgsql_post_column_ref ; 
 int /*<<< orphan*/  plpgsql_pre_column_ref ; 

void
plpgsql_parser_setup(struct ParseState *pstate, PLpgSQL_expr *expr)
{
	pstate->p_pre_columnref_hook = plpgsql_pre_column_ref;
	pstate->p_post_columnref_hook = plpgsql_post_column_ref;
	pstate->p_paramref_hook = plpgsql_param_ref;
	/* no need to use p_coerce_param_hook */
	pstate->p_ref_hook_state = (void *) expr;
}