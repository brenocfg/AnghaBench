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
struct TYPE_3__ {int /*<<< orphan*/  body; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ PLpgSQL_stmt_while ;

/* Variables and functions */
 int /*<<< orphan*/  free_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_stmts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_while(PLpgSQL_stmt_while *stmt)
{
	free_expr(stmt->cond);
	free_stmts(stmt->body);
}