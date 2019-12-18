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
struct TYPE_5__ {int /*<<< orphan*/  body; scalar_t__ step; scalar_t__ upper; scalar_t__ lower; scalar_t__ reverse; TYPE_1__* var; } ;
struct TYPE_4__ {char* refname; } ;
typedef  TYPE_2__ PLpgSQL_stmt_fori ;

/* Variables and functions */
 int /*<<< orphan*/  dump_expr (scalar_t__) ; 
 int /*<<< orphan*/  dump_ind () ; 
 int dump_indent ; 
 int /*<<< orphan*/  dump_stmts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_fori(PLpgSQL_stmt_fori *stmt)
{
	dump_ind();
	printf("FORI %s %s\n", stmt->var->refname, (stmt->reverse) ? "REVERSE" : "NORMAL");

	dump_indent += 2;
	dump_ind();
	printf("    lower = ");
	dump_expr(stmt->lower);
	printf("\n");
	dump_ind();
	printf("    upper = ");
	dump_expr(stmt->upper);
	printf("\n");
	if (stmt->step)
	{
		dump_ind();
		printf("    step = ");
		dump_expr(stmt->step);
		printf("\n");
	}
	dump_indent -= 2;

	dump_stmts(stmt->body);

	dump_ind();
	printf("    ENDFORI\n");
}