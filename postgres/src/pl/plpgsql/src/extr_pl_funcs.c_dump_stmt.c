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
struct TYPE_3__ {int lineno; int cmd_type; } ;
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

/* Variables and functions */
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
 int /*<<< orphan*/  dump_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_assign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_call (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_case (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_dynexecute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_dynfors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_execsql (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_fetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_forc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_foreach_a (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_fori (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_fors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_getdiag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_if (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_loop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_raise (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_return_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_return_query (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_rollback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_while (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
dump_stmt(PLpgSQL_stmt *stmt)
{
	printf("%3d:", stmt->lineno);
	switch (stmt->cmd_type)
	{
		case PLPGSQL_STMT_BLOCK:
			dump_block((PLpgSQL_stmt_block *) stmt);
			break;
		case PLPGSQL_STMT_ASSIGN:
			dump_assign((PLpgSQL_stmt_assign *) stmt);
			break;
		case PLPGSQL_STMT_IF:
			dump_if((PLpgSQL_stmt_if *) stmt);
			break;
		case PLPGSQL_STMT_CASE:
			dump_case((PLpgSQL_stmt_case *) stmt);
			break;
		case PLPGSQL_STMT_LOOP:
			dump_loop((PLpgSQL_stmt_loop *) stmt);
			break;
		case PLPGSQL_STMT_WHILE:
			dump_while((PLpgSQL_stmt_while *) stmt);
			break;
		case PLPGSQL_STMT_FORI:
			dump_fori((PLpgSQL_stmt_fori *) stmt);
			break;
		case PLPGSQL_STMT_FORS:
			dump_fors((PLpgSQL_stmt_fors *) stmt);
			break;
		case PLPGSQL_STMT_FORC:
			dump_forc((PLpgSQL_stmt_forc *) stmt);
			break;
		case PLPGSQL_STMT_FOREACH_A:
			dump_foreach_a((PLpgSQL_stmt_foreach_a *) stmt);
			break;
		case PLPGSQL_STMT_EXIT:
			dump_exit((PLpgSQL_stmt_exit *) stmt);
			break;
		case PLPGSQL_STMT_RETURN:
			dump_return((PLpgSQL_stmt_return *) stmt);
			break;
		case PLPGSQL_STMT_RETURN_NEXT:
			dump_return_next((PLpgSQL_stmt_return_next *) stmt);
			break;
		case PLPGSQL_STMT_RETURN_QUERY:
			dump_return_query((PLpgSQL_stmt_return_query *) stmt);
			break;
		case PLPGSQL_STMT_RAISE:
			dump_raise((PLpgSQL_stmt_raise *) stmt);
			break;
		case PLPGSQL_STMT_ASSERT:
			dump_assert((PLpgSQL_stmt_assert *) stmt);
			break;
		case PLPGSQL_STMT_EXECSQL:
			dump_execsql((PLpgSQL_stmt_execsql *) stmt);
			break;
		case PLPGSQL_STMT_DYNEXECUTE:
			dump_dynexecute((PLpgSQL_stmt_dynexecute *) stmt);
			break;
		case PLPGSQL_STMT_DYNFORS:
			dump_dynfors((PLpgSQL_stmt_dynfors *) stmt);
			break;
		case PLPGSQL_STMT_GETDIAG:
			dump_getdiag((PLpgSQL_stmt_getdiag *) stmt);
			break;
		case PLPGSQL_STMT_OPEN:
			dump_open((PLpgSQL_stmt_open *) stmt);
			break;
		case PLPGSQL_STMT_FETCH:
			dump_fetch((PLpgSQL_stmt_fetch *) stmt);
			break;
		case PLPGSQL_STMT_CLOSE:
			dump_close((PLpgSQL_stmt_close *) stmt);
			break;
		case PLPGSQL_STMT_PERFORM:
			dump_perform((PLpgSQL_stmt_perform *) stmt);
			break;
		case PLPGSQL_STMT_CALL:
			dump_call((PLpgSQL_stmt_call *) stmt);
			break;
		case PLPGSQL_STMT_COMMIT:
			dump_commit((PLpgSQL_stmt_commit *) stmt);
			break;
		case PLPGSQL_STMT_ROLLBACK:
			dump_rollback((PLpgSQL_stmt_rollback *) stmt);
			break;
		case PLPGSQL_STMT_SET:
			dump_set((PLpgSQL_stmt_set *) stmt);
			break;
		default:
			elog(ERROR, "unrecognized cmd_type: %d", stmt->cmd_type);
			break;
	}
}