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
struct TYPE_3__ {scalar_t__ retvarno; int /*<<< orphan*/ * expr; } ;
typedef  TYPE_1__ PLpgSQL_stmt_return_next ;

/* Variables and functions */
 int /*<<< orphan*/  dump_expr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_ind () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_return_next(PLpgSQL_stmt_return_next *stmt)
{
	dump_ind();
	printf("RETURN NEXT ");
	if (stmt->retvarno >= 0)
		printf("variable %d", stmt->retvarno);
	else if (stmt->expr != NULL)
		dump_expr(stmt->expr);
	else
		printf("NULL");
	printf("\n");
}