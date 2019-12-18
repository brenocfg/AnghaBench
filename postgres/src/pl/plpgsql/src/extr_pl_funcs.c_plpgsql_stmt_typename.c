#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int cmd_type; } ;
struct TYPE_10__ {int /*<<< orphan*/  is_call; } ;
struct TYPE_9__ {int /*<<< orphan*/  is_exit; } ;
struct TYPE_8__ {int /*<<< orphan*/  is_move; } ;
struct TYPE_7__ {int /*<<< orphan*/  is_stacked; } ;
typedef  TYPE_1__ PLpgSQL_stmt_getdiag ;
typedef  TYPE_2__ PLpgSQL_stmt_fetch ;
typedef  TYPE_3__ PLpgSQL_stmt_exit ;
typedef  TYPE_4__ PLpgSQL_stmt_call ;
typedef  TYPE_5__ PLpgSQL_stmt ;

/* Variables and functions */
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
 char const* _ (char*) ; 

const char *
plpgsql_stmt_typename(PLpgSQL_stmt *stmt)
{
	switch (stmt->cmd_type)
	{
		case PLPGSQL_STMT_BLOCK:
			return _("statement block");
		case PLPGSQL_STMT_ASSIGN:
			return _("assignment");
		case PLPGSQL_STMT_IF:
			return "IF";
		case PLPGSQL_STMT_CASE:
			return "CASE";
		case PLPGSQL_STMT_LOOP:
			return "LOOP";
		case PLPGSQL_STMT_WHILE:
			return "WHILE";
		case PLPGSQL_STMT_FORI:
			return _("FOR with integer loop variable");
		case PLPGSQL_STMT_FORS:
			return _("FOR over SELECT rows");
		case PLPGSQL_STMT_FORC:
			return _("FOR over cursor");
		case PLPGSQL_STMT_FOREACH_A:
			return _("FOREACH over array");
		case PLPGSQL_STMT_EXIT:
			return ((PLpgSQL_stmt_exit *) stmt)->is_exit ? "EXIT" : "CONTINUE";
		case PLPGSQL_STMT_RETURN:
			return "RETURN";
		case PLPGSQL_STMT_RETURN_NEXT:
			return "RETURN NEXT";
		case PLPGSQL_STMT_RETURN_QUERY:
			return "RETURN QUERY";
		case PLPGSQL_STMT_RAISE:
			return "RAISE";
		case PLPGSQL_STMT_ASSERT:
			return "ASSERT";
		case PLPGSQL_STMT_EXECSQL:
			return _("SQL statement");
		case PLPGSQL_STMT_DYNEXECUTE:
			return "EXECUTE";
		case PLPGSQL_STMT_DYNFORS:
			return _("FOR over EXECUTE statement");
		case PLPGSQL_STMT_GETDIAG:
			return ((PLpgSQL_stmt_getdiag *) stmt)->is_stacked ?
				"GET STACKED DIAGNOSTICS" : "GET DIAGNOSTICS";
		case PLPGSQL_STMT_OPEN:
			return "OPEN";
		case PLPGSQL_STMT_FETCH:
			return ((PLpgSQL_stmt_fetch *) stmt)->is_move ? "MOVE" : "FETCH";
		case PLPGSQL_STMT_CLOSE:
			return "CLOSE";
		case PLPGSQL_STMT_PERFORM:
			return "PERFORM";
		case PLPGSQL_STMT_CALL:
			return ((PLpgSQL_stmt_call *) stmt)->is_call ? "CALL" : "DO";
		case PLPGSQL_STMT_COMMIT:
			return "COMMIT";
		case PLPGSQL_STMT_ROLLBACK:
			return "ROLLBACK";
		case PLPGSQL_STMT_SET:
			return "SET";
	}

	return "unknown";
}