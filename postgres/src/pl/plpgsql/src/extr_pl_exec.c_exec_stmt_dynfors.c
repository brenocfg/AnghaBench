#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  params; int /*<<< orphan*/  query; } ;
typedef  int /*<<< orphan*/  Portal ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_forq ;
typedef  TYPE_1__ PLpgSQL_stmt_dynfors ;
typedef  int /*<<< orphan*/  PLpgSQL_execstate ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_cursor_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_dynquery_with_params (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int exec_for_query (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
exec_stmt_dynfors(PLpgSQL_execstate *estate, PLpgSQL_stmt_dynfors *stmt)
{
	Portal		portal;
	int			rc;

	portal = exec_dynquery_with_params(estate, stmt->query, stmt->params,
									   NULL, 0);

	/*
	 * Execute the loop
	 */
	rc = exec_for_query(estate, (PLpgSQL_stmt_forq *) stmt, portal, true);

	/*
	 * Close the implicit cursor
	 */
	SPI_cursor_close(portal);

	return rc;
}