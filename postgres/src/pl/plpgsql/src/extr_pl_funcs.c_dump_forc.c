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
struct TYPE_5__ {int curvar; int /*<<< orphan*/  body; int /*<<< orphan*/ * argquery; TYPE_1__* var; } ;
struct TYPE_4__ {char* refname; } ;
typedef  TYPE_2__ PLpgSQL_stmt_forc ;

/* Variables and functions */
 int /*<<< orphan*/  dump_expr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_ind () ; 
 int dump_indent ; 
 int /*<<< orphan*/  dump_stmts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_forc(PLpgSQL_stmt_forc *stmt)
{
	dump_ind();
	printf("FORC %s ", stmt->var->refname);
	printf("curvar=%d\n", stmt->curvar);

	dump_indent += 2;
	if (stmt->argquery != NULL)
	{
		dump_ind();
		printf("  arguments = ");
		dump_expr(stmt->argquery);
		printf("\n");
	}
	dump_indent -= 2;

	dump_stmts(stmt->body);

	dump_ind();
	printf("    ENDFORC\n");
}