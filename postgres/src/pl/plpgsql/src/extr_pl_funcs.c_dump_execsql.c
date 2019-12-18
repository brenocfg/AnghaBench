#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* target; scalar_t__ strict; int /*<<< orphan*/  sqlstmt; } ;
struct TYPE_4__ {int dno; char* refname; } ;
typedef  TYPE_2__ PLpgSQL_stmt_execsql ;

/* Variables and functions */
 int /*<<< orphan*/  dump_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_ind () ; 
 int dump_indent ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_execsql(PLpgSQL_stmt_execsql *stmt)
{
	dump_ind();
	printf("EXECSQL ");
	dump_expr(stmt->sqlstmt);
	printf("\n");

	dump_indent += 2;
	if (stmt->target != NULL)
	{
		dump_ind();
		printf("    INTO%s target = %d %s\n",
			   stmt->strict ? " STRICT" : "",
			   stmt->target->dno, stmt->target->refname);
	}
	dump_indent -= 2;
}