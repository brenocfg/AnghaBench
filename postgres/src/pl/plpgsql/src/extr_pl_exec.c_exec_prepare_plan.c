#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  func; } ;
struct TYPE_7__ {int rwparam; int /*<<< orphan*/ * plan; int /*<<< orphan*/  query; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/ * SPIPlanPtr ;
typedef  int /*<<< orphan*/  ParserSetupHook ;
typedef  TYPE_1__ PLpgSQL_expr ;
typedef  TYPE_2__ PLpgSQL_execstate ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  SPI_keepplan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SPI_prepare_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  SPI_result ; 
 int /*<<< orphan*/  SPI_result_code_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_simple_check_plan (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ plpgsql_parser_setup ; 

__attribute__((used)) static void
exec_prepare_plan(PLpgSQL_execstate *estate,
				  PLpgSQL_expr *expr, int cursorOptions,
				  bool keepplan)
{
	SPIPlanPtr	plan;

	/*
	 * The grammar can't conveniently set expr->func while building the parse
	 * tree, so make sure it's set before parser hooks need it.
	 */
	expr->func = estate->func;

	/*
	 * Generate and save the plan
	 */
	plan = SPI_prepare_params(expr->query,
							  (ParserSetupHook) plpgsql_parser_setup,
							  (void *) expr,
							  cursorOptions);
	if (plan == NULL)
		elog(ERROR, "SPI_prepare_params failed for \"%s\": %s",
			 expr->query, SPI_result_code_string(SPI_result));
	if (keepplan)
		SPI_keepplan(plan);
	expr->plan = plan;

	/* Check to see if it's a simple expression */
	exec_simple_check_plan(estate, expr);

	/*
	 * Mark expression as not using a read-write param.  exec_assign_value has
	 * to take steps to override this if appropriate; that seems cleaner than
	 * adding parameters to all other callers.
	 */
	expr->rwparam = -1;
}