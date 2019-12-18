#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_10__ {scalar_t__ dtype; int /*<<< orphan*/  dno; } ;
struct TYPE_9__ {int /*<<< orphan*/ * plan; } ;
typedef  TYPE_1__ PLpgSQL_expr ;
typedef  int /*<<< orphan*/  PLpgSQL_execstate ;
typedef  TYPE_2__ PLpgSQL_datum ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ PLPGSQL_DTYPE_VAR ; 
 int /*<<< orphan*/  exec_assign_value (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_check_rw_parameter (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_eval_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_eval_expr (int /*<<< orphan*/ *,TYPE_1__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_prepare_plan (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
exec_assign_expr(PLpgSQL_execstate *estate, PLpgSQL_datum *target,
				 PLpgSQL_expr *expr)
{
	Datum		value;
	bool		isnull;
	Oid			valtype;
	int32		valtypmod;

	/*
	 * If first time through, create a plan for this expression, and then see
	 * if we can pass the target variable as a read-write parameter to the
	 * expression.  (This is a bit messy, but it seems cleaner than modifying
	 * the API of exec_eval_expr for the purpose.)
	 */
	if (expr->plan == NULL)
	{
		exec_prepare_plan(estate, expr, 0, true);
		if (target->dtype == PLPGSQL_DTYPE_VAR)
			exec_check_rw_parameter(expr, target->dno);
	}

	value = exec_eval_expr(estate, expr, &isnull, &valtype, &valtypmod);
	exec_assign_value(estate, target, value, isnull, valtype, valtypmod);
	exec_eval_cleanup(estate);
}