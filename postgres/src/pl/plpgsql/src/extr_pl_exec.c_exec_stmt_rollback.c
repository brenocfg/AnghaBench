#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * simple_eval_estate; } ;
struct TYPE_6__ {scalar_t__ chain; } ;
typedef  TYPE_1__ PLpgSQL_stmt_rollback ;
typedef  TYPE_2__ PLpgSQL_execstate ;

/* Variables and functions */
 int PLPGSQL_RC_OK ; 
 int /*<<< orphan*/  SPI_rollback () ; 
 int /*<<< orphan*/  SPI_rollback_and_chain () ; 
 int /*<<< orphan*/  SPI_start_transaction () ; 
 int /*<<< orphan*/  plpgsql_create_econtext (TYPE_2__*) ; 

__attribute__((used)) static int
exec_stmt_rollback(PLpgSQL_execstate *estate, PLpgSQL_stmt_rollback *stmt)
{
	if (stmt->chain)
		SPI_rollback_and_chain();
	else
	{
		SPI_rollback();
		SPI_start_transaction();
	}

	estate->simple_eval_estate = NULL;
	plpgsql_create_econtext(estate);

	return PLPGSQL_RC_OK;
}