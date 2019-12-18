#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int PLpgSQL_getdiag_kind ;

/* Variables and functions */
#define  PLPGSQL_GETDIAG_COLUMN_NAME 139 
#define  PLPGSQL_GETDIAG_CONSTRAINT_NAME 138 
#define  PLPGSQL_GETDIAG_CONTEXT 137 
#define  PLPGSQL_GETDIAG_DATATYPE_NAME 136 
#define  PLPGSQL_GETDIAG_ERROR_CONTEXT 135 
#define  PLPGSQL_GETDIAG_ERROR_DETAIL 134 
#define  PLPGSQL_GETDIAG_ERROR_HINT 133 
#define  PLPGSQL_GETDIAG_MESSAGE_TEXT 132 
#define  PLPGSQL_GETDIAG_RETURNED_SQLSTATE 131 
#define  PLPGSQL_GETDIAG_ROW_COUNT 130 
#define  PLPGSQL_GETDIAG_SCHEMA_NAME 129 
#define  PLPGSQL_GETDIAG_TABLE_NAME 128 

const char *
plpgsql_getdiag_kindname(PLpgSQL_getdiag_kind kind)
{
	switch (kind)
	{
		case PLPGSQL_GETDIAG_ROW_COUNT:
			return "ROW_COUNT";
		case PLPGSQL_GETDIAG_CONTEXT:
			return "PG_CONTEXT";
		case PLPGSQL_GETDIAG_ERROR_CONTEXT:
			return "PG_EXCEPTION_CONTEXT";
		case PLPGSQL_GETDIAG_ERROR_DETAIL:
			return "PG_EXCEPTION_DETAIL";
		case PLPGSQL_GETDIAG_ERROR_HINT:
			return "PG_EXCEPTION_HINT";
		case PLPGSQL_GETDIAG_RETURNED_SQLSTATE:
			return "RETURNED_SQLSTATE";
		case PLPGSQL_GETDIAG_COLUMN_NAME:
			return "COLUMN_NAME";
		case PLPGSQL_GETDIAG_CONSTRAINT_NAME:
			return "CONSTRAINT_NAME";
		case PLPGSQL_GETDIAG_DATATYPE_NAME:
			return "PG_DATATYPE_NAME";
		case PLPGSQL_GETDIAG_MESSAGE_TEXT:
			return "MESSAGE_TEXT";
		case PLPGSQL_GETDIAG_TABLE_NAME:
			return "TABLE_NAME";
		case PLPGSQL_GETDIAG_SCHEMA_NAME:
			return "SCHEMA_NAME";
	}

	return "unknown";
}