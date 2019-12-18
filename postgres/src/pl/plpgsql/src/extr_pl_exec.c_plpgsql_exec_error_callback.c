#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lineno; } ;
struct TYPE_5__ {TYPE_1__* func; TYPE_3__* err_stmt; int /*<<< orphan*/ * err_text; } ;
struct TYPE_4__ {int /*<<< orphan*/  fn_signature; } ;
typedef  TYPE_2__ PLpgSQL_execstate ;

/* Variables and functions */
 int /*<<< orphan*/  _ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errcontext (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  plpgsql_stmt_typename (TYPE_3__*) ; 

__attribute__((used)) static void
plpgsql_exec_error_callback(void *arg)
{
	PLpgSQL_execstate *estate = (PLpgSQL_execstate *) arg;

	if (estate->err_text != NULL)
	{
		/*
		 * We don't expend the cycles to run gettext() on err_text unless we
		 * actually need it.  Therefore, places that set up err_text should
		 * use gettext_noop() to ensure the strings get recorded in the
		 * message dictionary.
		 *
		 * If both err_text and err_stmt are set, use the err_text as
		 * description, but report the err_stmt's line number.  When err_stmt
		 * is not set, we're in function entry/exit, or some such place not
		 * attached to a specific line number.
		 */
		if (estate->err_stmt != NULL)
		{
			/*
			 * translator: last %s is a phrase such as "during statement block
			 * local variable initialization"
			 */
			errcontext("PL/pgSQL function %s line %d %s",
					   estate->func->fn_signature,
					   estate->err_stmt->lineno,
					   _(estate->err_text));
		}
		else
		{
			/*
			 * translator: last %s is a phrase such as "while storing call
			 * arguments into local variables"
			 */
			errcontext("PL/pgSQL function %s %s",
					   estate->func->fn_signature,
					   _(estate->err_text));
		}
	}
	else if (estate->err_stmt != NULL)
	{
		/* translator: last %s is a plpgsql statement type name */
		errcontext("PL/pgSQL function %s line %d at %s",
				   estate->func->fn_signature,
				   estate->err_stmt->lineno,
				   plpgsql_stmt_typename(estate->err_stmt));
	}
	else
		errcontext("PL/pgSQL function %s",
				   estate->func->fn_signature);
}