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
typedef  int ParseExprKind ;

/* Variables and functions */
#define  EXPR_KIND_ALTER_COL_TRANSFORM 168 
#define  EXPR_KIND_CALL_ARGUMENT 167 
#define  EXPR_KIND_CHECK_CONSTRAINT 166 
#define  EXPR_KIND_COLUMN_DEFAULT 165 
#define  EXPR_KIND_COPY_WHERE 164 
#define  EXPR_KIND_DISTINCT_ON 163 
#define  EXPR_KIND_DOMAIN_CHECK 162 
#define  EXPR_KIND_EXECUTE_PARAMETER 161 
#define  EXPR_KIND_FILTER 160 
#define  EXPR_KIND_FROM_FUNCTION 159 
#define  EXPR_KIND_FROM_SUBSELECT 158 
#define  EXPR_KIND_FUNCTION_DEFAULT 157 
#define  EXPR_KIND_GENERATED_COLUMN 156 
#define  EXPR_KIND_GROUP_BY 155 
#define  EXPR_KIND_HAVING 154 
#define  EXPR_KIND_INDEX_EXPRESSION 153 
#define  EXPR_KIND_INDEX_PREDICATE 152 
#define  EXPR_KIND_INSERT_TARGET 151 
#define  EXPR_KIND_JOIN_ON 150 
#define  EXPR_KIND_JOIN_USING 149 
#define  EXPR_KIND_LIMIT 148 
#define  EXPR_KIND_NONE 147 
#define  EXPR_KIND_OFFSET 146 
#define  EXPR_KIND_ORDER_BY 145 
#define  EXPR_KIND_OTHER 144 
#define  EXPR_KIND_PARTITION_BOUND 143 
#define  EXPR_KIND_PARTITION_EXPRESSION 142 
#define  EXPR_KIND_POLICY 141 
#define  EXPR_KIND_RETURNING 140 
#define  EXPR_KIND_SELECT_TARGET 139 
#define  EXPR_KIND_TRIGGER_WHEN 138 
#define  EXPR_KIND_UPDATE_SOURCE 137 
#define  EXPR_KIND_UPDATE_TARGET 136 
#define  EXPR_KIND_VALUES 135 
#define  EXPR_KIND_VALUES_SINGLE 134 
#define  EXPR_KIND_WHERE 133 
#define  EXPR_KIND_WINDOW_FRAME_GROUPS 132 
#define  EXPR_KIND_WINDOW_FRAME_RANGE 131 
#define  EXPR_KIND_WINDOW_FRAME_ROWS 130 
#define  EXPR_KIND_WINDOW_ORDER 129 
#define  EXPR_KIND_WINDOW_PARTITION 128 

const char *
ParseExprKindName(ParseExprKind exprKind)
{
	switch (exprKind)
	{
		case EXPR_KIND_NONE:
			return "invalid expression context";
		case EXPR_KIND_OTHER:
			return "extension expression";
		case EXPR_KIND_JOIN_ON:
			return "JOIN/ON";
		case EXPR_KIND_JOIN_USING:
			return "JOIN/USING";
		case EXPR_KIND_FROM_SUBSELECT:
			return "sub-SELECT in FROM";
		case EXPR_KIND_FROM_FUNCTION:
			return "function in FROM";
		case EXPR_KIND_WHERE:
			return "WHERE";
		case EXPR_KIND_POLICY:
			return "POLICY";
		case EXPR_KIND_HAVING:
			return "HAVING";
		case EXPR_KIND_FILTER:
			return "FILTER";
		case EXPR_KIND_WINDOW_PARTITION:
			return "window PARTITION BY";
		case EXPR_KIND_WINDOW_ORDER:
			return "window ORDER BY";
		case EXPR_KIND_WINDOW_FRAME_RANGE:
			return "window RANGE";
		case EXPR_KIND_WINDOW_FRAME_ROWS:
			return "window ROWS";
		case EXPR_KIND_WINDOW_FRAME_GROUPS:
			return "window GROUPS";
		case EXPR_KIND_SELECT_TARGET:
			return "SELECT";
		case EXPR_KIND_INSERT_TARGET:
			return "INSERT";
		case EXPR_KIND_UPDATE_SOURCE:
		case EXPR_KIND_UPDATE_TARGET:
			return "UPDATE";
		case EXPR_KIND_GROUP_BY:
			return "GROUP BY";
		case EXPR_KIND_ORDER_BY:
			return "ORDER BY";
		case EXPR_KIND_DISTINCT_ON:
			return "DISTINCT ON";
		case EXPR_KIND_LIMIT:
			return "LIMIT";
		case EXPR_KIND_OFFSET:
			return "OFFSET";
		case EXPR_KIND_RETURNING:
			return "RETURNING";
		case EXPR_KIND_VALUES:
		case EXPR_KIND_VALUES_SINGLE:
			return "VALUES";
		case EXPR_KIND_CHECK_CONSTRAINT:
		case EXPR_KIND_DOMAIN_CHECK:
			return "CHECK";
		case EXPR_KIND_COLUMN_DEFAULT:
		case EXPR_KIND_FUNCTION_DEFAULT:
			return "DEFAULT";
		case EXPR_KIND_INDEX_EXPRESSION:
			return "index expression";
		case EXPR_KIND_INDEX_PREDICATE:
			return "index predicate";
		case EXPR_KIND_ALTER_COL_TRANSFORM:
			return "USING";
		case EXPR_KIND_EXECUTE_PARAMETER:
			return "EXECUTE";
		case EXPR_KIND_TRIGGER_WHEN:
			return "WHEN";
		case EXPR_KIND_PARTITION_BOUND:
			return "partition bound";
		case EXPR_KIND_PARTITION_EXPRESSION:
			return "PARTITION BY";
		case EXPR_KIND_CALL_ARGUMENT:
			return "CALL";
		case EXPR_KIND_COPY_WHERE:
			return "WHERE";
		case EXPR_KIND_GENERATED_COLUMN:
			return "GENERATED AS";

			/*
			 * There is intentionally no default: case here, so that the
			 * compiler will warn if we add a new ParseExprKind without
			 * extending this switch.  If we do see an unrecognized value at
			 * runtime, we'll fall through to the "unrecognized" return.
			 */
	}
	return "unrecognized expression kind";
}