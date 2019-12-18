#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int no_snapshots; } ;
struct TYPE_11__ {int /*<<< orphan*/  readonly_func; } ;
struct TYPE_10__ {int /*<<< orphan*/  query; TYPE_8__* plan; } ;
struct TYPE_9__ {TYPE_2__* expr; } ;
typedef  TYPE_1__ PLpgSQL_stmt_set ;
typedef  TYPE_2__ PLpgSQL_expr ;
typedef  TYPE_3__ PLpgSQL_execstate ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int PLPGSQL_RC_OK ; 
 int SPI_OK_UTILITY ; 
 int SPI_execute_plan (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_result_code_string (int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_prepare_plan (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
exec_stmt_set(PLpgSQL_execstate *estate, PLpgSQL_stmt_set *stmt)
{
	PLpgSQL_expr *expr = stmt->expr;
	int			rc;

	if (expr->plan == NULL)
	{
		exec_prepare_plan(estate, expr, 0, true);
		expr->plan->no_snapshots = true;
	}

	rc = SPI_execute_plan(expr->plan, NULL, NULL, estate->readonly_func, 0);

	if (rc != SPI_OK_UTILITY)
		elog(ERROR, "SPI_execute_plan failed executing query \"%s\": %s",
			 expr->query, SPI_result_code_string(rc));

	return PLPGSQL_RC_OK;
}