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
struct TYPE_3__ {int /*<<< orphan*/ * message; int /*<<< orphan*/ * cond; } ;
typedef  TYPE_1__ PLpgSQL_stmt_assert ;

/* Variables and functions */
 int /*<<< orphan*/  dump_expr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_ind () ; 
 int dump_indent ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
dump_assert(PLpgSQL_stmt_assert *stmt)
{
	dump_ind();
	printf("ASSERT ");
	dump_expr(stmt->cond);
	printf("\n");

	dump_indent += 2;
	if (stmt->message != NULL)
	{
		dump_ind();
		printf("    MESSAGE = ");
		dump_expr(stmt->message);
		printf("\n");
	}
	dump_indent -= 2;
}