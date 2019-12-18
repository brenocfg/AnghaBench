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
struct TYPE_5__ {int /*<<< orphan*/  body; int /*<<< orphan*/  query; TYPE_1__* var; } ;
struct TYPE_4__ {char* refname; } ;
typedef  TYPE_2__ PLpgSQL_stmt_fors ;

/* Variables and functions */
 int /*<<< orphan*/  dump_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_ind () ; 
 int /*<<< orphan*/  dump_stmts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_fors(PLpgSQL_stmt_fors *stmt)
{
	dump_ind();
	printf("FORS %s ", stmt->var->refname);
	dump_expr(stmt->query);
	printf("\n");

	dump_stmts(stmt->body);

	dump_ind();
	printf("    ENDFORS\n");
}