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
typedef  int /*<<< orphan*/  backslashResult ;
typedef  int /*<<< orphan*/  PsqlScanState ;
typedef  int /*<<< orphan*/  PQExpBuffer ;
typedef  int /*<<< orphan*/  ConditionalStack ;

/* Variables and functions */
 int /*<<< orphan*/  IFSTATE_FALSE ; 
 int /*<<< orphan*/  IFSTATE_IGNORED ; 
 int /*<<< orphan*/  IFSTATE_TRUE ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 scalar_t__ conditional_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conditional_stack_poke (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conditional_stack_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore_boolean_expression (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_true_boolean_expression (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  save_query_text_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static backslashResult
exec_command_if(PsqlScanState scan_state, ConditionalStack cstack,
				PQExpBuffer query_buf)
{
	if (conditional_active(cstack))
	{
		/*
		 * First, push a new active stack entry; this ensures that the lexer
		 * will perform variable substitution and backtick evaluation while
		 * scanning the expression.  (That should happen anyway, since we know
		 * we're in an active outer branch, but let's be sure.)
		 */
		conditional_stack_push(cstack, IFSTATE_TRUE);

		/* Remember current query state in case we need to restore later */
		save_query_text_state(scan_state, cstack, query_buf);

		/*
		 * Evaluate the expression; if it's false, change to inactive state.
		 */
		if (!is_true_boolean_expression(scan_state, "\\if expression"))
			conditional_stack_poke(cstack, IFSTATE_FALSE);
	}
	else
	{
		/*
		 * We're within an inactive outer branch, so this entire \if block
		 * will be ignored.  We don't want to evaluate the expression, so push
		 * the "ignored" stack state before scanning it.
		 */
		conditional_stack_push(cstack, IFSTATE_IGNORED);

		/* Remember current query state in case we need to restore later */
		save_query_text_state(scan_state, cstack, query_buf);

		ignore_boolean_expression(scan_state);
	}

	return PSQL_CMD_SKIP_LINE;
}