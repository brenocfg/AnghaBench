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
struct TYPE_3__ {int varno; scalar_t__ slice; int /*<<< orphan*/  body; int /*<<< orphan*/  expr; } ;
typedef  TYPE_1__ PLpgSQL_stmt_foreach_a ;

/* Variables and functions */
 int /*<<< orphan*/  dump_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_ind () ; 
 int /*<<< orphan*/  dump_stmts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_foreach_a(PLpgSQL_stmt_foreach_a *stmt)
{
	dump_ind();
	printf("FOREACHA var %d ", stmt->varno);
	if (stmt->slice != 0)
		printf("SLICE %d ", stmt->slice);
	printf("IN ");
	dump_expr(stmt->expr);
	printf("\n");

	dump_stmts(stmt->body);

	dump_ind();
	printf("    ENDFOREACHA");
}