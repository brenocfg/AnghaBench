#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* action; int /*<<< orphan*/  out_param_varno; scalar_t__ nstatements; } ;
struct TYPE_10__ {scalar_t__ cmd_type; } ;
struct TYPE_9__ {scalar_t__ body; scalar_t__ stmtid; int /*<<< orphan*/  cmd_type; int /*<<< orphan*/ * exceptions; } ;
struct TYPE_8__ {int /*<<< orphan*/  retvarno; int /*<<< orphan*/ * expr; scalar_t__ stmtid; scalar_t__ cmd_type; } ;
typedef  TYPE_1__ PLpgSQL_stmt_return ;
typedef  TYPE_2__ PLpgSQL_stmt_block ;
typedef  TYPE_3__ PLpgSQL_stmt ;
typedef  TYPE_4__ PLpgSQL_function ;

/* Variables and functions */
 scalar_t__ NIL ; 
 int /*<<< orphan*/  PLPGSQL_STMT_BLOCK ; 
 scalar_t__ PLPGSQL_STMT_RETURN ; 
 scalar_t__ lappend (scalar_t__,TYPE_1__*) ; 
 scalar_t__ list_make1 (TYPE_2__*) ; 
 scalar_t__ llast (scalar_t__) ; 
 void* palloc0 (int) ; 

__attribute__((used)) static void
add_dummy_return(PLpgSQL_function *function)
{
	/*
	 * If the outer block has an EXCEPTION clause, we need to make a new outer
	 * block, since the added RETURN shouldn't act like it is inside the
	 * EXCEPTION clause.
	 */
	if (function->action->exceptions != NULL)
	{
		PLpgSQL_stmt_block *new;

		new = palloc0(sizeof(PLpgSQL_stmt_block));
		new->cmd_type = PLPGSQL_STMT_BLOCK;
		new->stmtid = ++function->nstatements;
		new->body = list_make1(function->action);

		function->action = new;
	}
	if (function->action->body == NIL ||
		((PLpgSQL_stmt *) llast(function->action->body))->cmd_type != PLPGSQL_STMT_RETURN)
	{
		PLpgSQL_stmt_return *new;

		new = palloc0(sizeof(PLpgSQL_stmt_return));
		new->cmd_type = PLPGSQL_STMT_RETURN;
		new->stmtid = ++function->nstatements;
		new->expr = NULL;
		new->retvarno = function->out_param_varno;

		function->action->body = lappend(function->action->body, new);
	}
}