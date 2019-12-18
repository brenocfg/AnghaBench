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
struct TYPE_4__ {char* str; int /*<<< orphan*/  ival; } ;
struct TYPE_5__ {int type; TYPE_1__ val; } ;
typedef  TYPE_2__ Value ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  T_BitString 132 
#define  T_Float 131 
#define  T_Integer 130 
#define  T_Null 129 
#define  T_String 128 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  outToken (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
_outValue(StringInfo str, const Value *value)
{
	switch (value->type)
	{
		case T_Integer:
			appendStringInfo(str, "%d", value->val.ival);
			break;
		case T_Float:

			/*
			 * We assume the value is a valid numeric literal and so does not
			 * need quoting.
			 */
			appendStringInfoString(str, value->val.str);
			break;
		case T_String:

			/*
			 * We use outToken to provide escaping of the string's content,
			 * but we don't want it to do anything with an empty string.
			 */
			appendStringInfoChar(str, '"');
			if (value->val.str[0] != '\0')
				outToken(str, value->val.str);
			appendStringInfoChar(str, '"');
			break;
		case T_BitString:
			/* internal representation already has leading 'b' */
			appendStringInfoString(str, value->val.str);
			break;
		case T_Null:
			/* this is seen only within A_Const, not in transformed trees */
			appendStringInfoString(str, "NULL");
			break;
		default:
			elog(ERROR, "unrecognized node type: %d", (int) value->type);
			break;
	}
}