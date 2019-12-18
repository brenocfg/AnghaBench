#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ eval_processed; } ;
struct TYPE_8__ {int /*<<< orphan*/ * expr; } ;
typedef  TYPE_1__ PLpgSQL_stmt_perform ;
typedef  int /*<<< orphan*/  PLpgSQL_expr ;
typedef  TYPE_2__ PLpgSQL_execstate ;

/* Variables and functions */
 int PLPGSQL_RC_OK ; 
 int /*<<< orphan*/  exec_eval_cleanup (TYPE_2__*) ; 
 int /*<<< orphan*/  exec_run_select (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_set_found (TYPE_2__*,int) ; 

__attribute__((used)) static int
exec_stmt_perform(PLpgSQL_execstate *estate, PLpgSQL_stmt_perform *stmt)
{
	PLpgSQL_expr *expr = stmt->expr;

	(void) exec_run_select(estate, expr, 0, NULL);
	exec_set_found(estate, (estate->eval_processed != 0));
	exec_eval_cleanup(estate);

	return PLPGSQL_RC_OK;
}