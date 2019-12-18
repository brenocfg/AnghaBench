#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;

/* Type definitions */
struct TYPE_40__ {int /*<<< orphan*/  (* stmt_end ) (TYPE_2__*,TYPE_1__*) ;int /*<<< orphan*/  (* stmt_beg ) (TYPE_2__*,TYPE_1__*) ;} ;
struct TYPE_39__ {TYPE_1__* err_stmt; } ;
struct TYPE_38__ {int cmd_type; } ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_while ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_set ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_rollback ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_return_query ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_return_next ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_return ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_raise ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_perform ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_open ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_loop ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_if ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_getdiag ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_fors ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_fori ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_foreach_a ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_forc ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_fetch ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_exit ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_execsql ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_dynfors ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_dynexecute ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_commit ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_close ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_case ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_call ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_block ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_assign ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_assert ;
typedef  TYPE_1__ PLpgSQL_stmt ;
typedef  TYPE_2__ PLpgSQL_execstate ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERROR ; 
#define  PLPGSQL_STMT_ASSERT 155 
#define  PLPGSQL_STMT_ASSIGN 154 
#define  PLPGSQL_STMT_BLOCK 153 
#define  PLPGSQL_STMT_CALL 152 
#define  PLPGSQL_STMT_CASE 151 
#define  PLPGSQL_STMT_CLOSE 150 
#define  PLPGSQL_STMT_COMMIT 149 
#define  PLPGSQL_STMT_DYNEXECUTE 148 
#define  PLPGSQL_STMT_DYNFORS 147 
#define  PLPGSQL_STMT_EXECSQL 146 
#define  PLPGSQL_STMT_EXIT 145 
#define  PLPGSQL_STMT_FETCH 144 
#define  PLPGSQL_STMT_FORC 143 
#define  PLPGSQL_STMT_FOREACH_A 142 
#define  PLPGSQL_STMT_FORI 141 
#define  PLPGSQL_STMT_FORS 140 
#define  PLPGSQL_STMT_GETDIAG 139 
#define  PLPGSQL_STMT_IF 138 
#define  PLPGSQL_STMT_LOOP 137 
#define  PLPGSQL_STMT_OPEN 136 
#define  PLPGSQL_STMT_PERFORM 135 
#define  PLPGSQL_STMT_RAISE 134 
#define  PLPGSQL_STMT_RETURN 133 
#define  PLPGSQL_STMT_RETURN_NEXT 132 
#define  PLPGSQL_STMT_RETURN_QUERY 131 
#define  PLPGSQL_STMT_ROLLBACK 130 
#define  PLPGSQL_STMT_SET 129 
#define  PLPGSQL_STMT_WHILE 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int exec_stmt_assert (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_assign (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_block (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_call (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_case (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_close (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_commit (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_dynexecute (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_dynfors (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_execsql (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_exit (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_fetch (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_forc (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_foreach_a (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_fori (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_fors (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_getdiag (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_if (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_loop (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_open (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_perform (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_raise (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_return (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_return_next (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_return_query (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_rollback (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_set (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int exec_stmt_while (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_7__** plpgsql_plugin_ptr ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int
exec_stmt(PLpgSQL_execstate *estate, PLpgSQL_stmt *stmt)
{
	PLpgSQL_stmt *save_estmt;
	int			rc = -1;

	save_estmt = estate->err_stmt;
	estate->err_stmt = stmt;

	/* Let the plugin know that we are about to execute this statement */
	if (*plpgsql_plugin_ptr && (*plpgsql_plugin_ptr)->stmt_beg)
		((*plpgsql_plugin_ptr)->stmt_beg) (estate, stmt);

	CHECK_FOR_INTERRUPTS();

	switch (stmt->cmd_type)
	{
		case PLPGSQL_STMT_BLOCK:
			rc = exec_stmt_block(estate, (PLpgSQL_stmt_block *) stmt);
			break;

		case PLPGSQL_STMT_ASSIGN:
			rc = exec_stmt_assign(estate, (PLpgSQL_stmt_assign *) stmt);
			break;

		case PLPGSQL_STMT_PERFORM:
			rc = exec_stmt_perform(estate, (PLpgSQL_stmt_perform *) stmt);
			break;

		case PLPGSQL_STMT_CALL:
			rc = exec_stmt_call(estate, (PLpgSQL_stmt_call *) stmt);
			break;

		case PLPGSQL_STMT_GETDIAG:
			rc = exec_stmt_getdiag(estate, (PLpgSQL_stmt_getdiag *) stmt);
			break;

		case PLPGSQL_STMT_IF:
			rc = exec_stmt_if(estate, (PLpgSQL_stmt_if *) stmt);
			break;

		case PLPGSQL_STMT_CASE:
			rc = exec_stmt_case(estate, (PLpgSQL_stmt_case *) stmt);
			break;

		case PLPGSQL_STMT_LOOP:
			rc = exec_stmt_loop(estate, (PLpgSQL_stmt_loop *) stmt);
			break;

		case PLPGSQL_STMT_WHILE:
			rc = exec_stmt_while(estate, (PLpgSQL_stmt_while *) stmt);
			break;

		case PLPGSQL_STMT_FORI:
			rc = exec_stmt_fori(estate, (PLpgSQL_stmt_fori *) stmt);
			break;

		case PLPGSQL_STMT_FORS:
			rc = exec_stmt_fors(estate, (PLpgSQL_stmt_fors *) stmt);
			break;

		case PLPGSQL_STMT_FORC:
			rc = exec_stmt_forc(estate, (PLpgSQL_stmt_forc *) stmt);
			break;

		case PLPGSQL_STMT_FOREACH_A:
			rc = exec_stmt_foreach_a(estate, (PLpgSQL_stmt_foreach_a *) stmt);
			break;

		case PLPGSQL_STMT_EXIT:
			rc = exec_stmt_exit(estate, (PLpgSQL_stmt_exit *) stmt);
			break;

		case PLPGSQL_STMT_RETURN:
			rc = exec_stmt_return(estate, (PLpgSQL_stmt_return *) stmt);
			break;

		case PLPGSQL_STMT_RETURN_NEXT:
			rc = exec_stmt_return_next(estate, (PLpgSQL_stmt_return_next *) stmt);
			break;

		case PLPGSQL_STMT_RETURN_QUERY:
			rc = exec_stmt_return_query(estate, (PLpgSQL_stmt_return_query *) stmt);
			break;

		case PLPGSQL_STMT_RAISE:
			rc = exec_stmt_raise(estate, (PLpgSQL_stmt_raise *) stmt);
			break;

		case PLPGSQL_STMT_ASSERT:
			rc = exec_stmt_assert(estate, (PLpgSQL_stmt_assert *) stmt);
			break;

		case PLPGSQL_STMT_EXECSQL:
			rc = exec_stmt_execsql(estate, (PLpgSQL_stmt_execsql *) stmt);
			break;

		case PLPGSQL_STMT_DYNEXECUTE:
			rc = exec_stmt_dynexecute(estate, (PLpgSQL_stmt_dynexecute *) stmt);
			break;

		case PLPGSQL_STMT_DYNFORS:
			rc = exec_stmt_dynfors(estate, (PLpgSQL_stmt_dynfors *) stmt);
			break;

		case PLPGSQL_STMT_OPEN:
			rc = exec_stmt_open(estate, (PLpgSQL_stmt_open *) stmt);
			break;

		case PLPGSQL_STMT_FETCH:
			rc = exec_stmt_fetch(estate, (PLpgSQL_stmt_fetch *) stmt);
			break;

		case PLPGSQL_STMT_CLOSE:
			rc = exec_stmt_close(estate, (PLpgSQL_stmt_close *) stmt);
			break;

		case PLPGSQL_STMT_COMMIT:
			rc = exec_stmt_commit(estate, (PLpgSQL_stmt_commit *) stmt);
			break;

		case PLPGSQL_STMT_ROLLBACK:
			rc = exec_stmt_rollback(estate, (PLpgSQL_stmt_rollback *) stmt);
			break;

		case PLPGSQL_STMT_SET:
			rc = exec_stmt_set(estate, (PLpgSQL_stmt_set *) stmt);
			break;

		default:
			estate->err_stmt = save_estmt;
			elog(ERROR, "unrecognized cmd_type: %d", stmt->cmd_type);
	}

	/* Let the plugin know that we have finished executing this statement */
	if (*plpgsql_plugin_ptr && (*plpgsql_plugin_ptr)->stmt_end)
		((*plpgsql_plugin_ptr)->stmt_end) (estate, stmt);

	estate->err_stmt = save_estmt;

	return rc;
}