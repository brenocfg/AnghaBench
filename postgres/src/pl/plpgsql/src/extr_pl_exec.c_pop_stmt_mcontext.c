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
struct TYPE_3__ {int /*<<< orphan*/  stmt_mcontext; int /*<<< orphan*/  stmt_mcontext_parent; } ;
typedef  TYPE_1__ PLpgSQL_execstate ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextGetParent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pop_stmt_mcontext(PLpgSQL_execstate *estate)
{
	/* We need only pop the stack */
	estate->stmt_mcontext = estate->stmt_mcontext_parent;
	estate->stmt_mcontext_parent = MemoryContextGetParent(estate->stmt_mcontext);
}