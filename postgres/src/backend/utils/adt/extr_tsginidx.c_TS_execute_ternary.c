#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* need_recheck; } ;
struct TYPE_7__ {int oper; int /*<<< orphan*/  left; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_1__ qoperator; } ;
typedef  int /*<<< orphan*/  QueryOperand ;
typedef  TYPE_2__ QueryItem ;
typedef  int GinTernaryValue ;
typedef  TYPE_3__ GinChkVal ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int GIN_FALSE ; 
 int GIN_MAYBE ; 
 int GIN_TRUE ; 
#define  OP_AND 131 
#define  OP_NOT 130 
#define  OP_OR 129 
#define  OP_PHRASE 128 
 scalar_t__ QI_VAL ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int checkcondition_gin_internal (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static GinTernaryValue
TS_execute_ternary(GinChkVal *gcv, QueryItem *curitem, bool in_phrase)
{
	GinTernaryValue val1,
				val2,
				result;

	/* since this function recurses, it could be driven to stack overflow */
	check_stack_depth();

	if (curitem->type == QI_VAL)
		return
			checkcondition_gin_internal(gcv,
										(QueryOperand *) curitem,
										NULL /* don't have position info */ );

	switch (curitem->qoperator.oper)
	{
		case OP_NOT:
			/* In phrase search, always return MAYBE since we lack positions */
			if (in_phrase)
				return GIN_MAYBE;
			result = TS_execute_ternary(gcv, curitem + 1, in_phrase);
			if (result == GIN_MAYBE)
				return result;
			return !result;

		case OP_PHRASE:

			/*
			 * GIN doesn't contain any information about positions, so treat
			 * OP_PHRASE as OP_AND with recheck requirement
			 */
			*(gcv->need_recheck) = true;
			/* Pass down in_phrase == true in case there's a NOT below */
			in_phrase = true;

			/* FALL THRU */

		case OP_AND:
			val1 = TS_execute_ternary(gcv, curitem + curitem->qoperator.left,
									  in_phrase);
			if (val1 == GIN_FALSE)
				return GIN_FALSE;
			val2 = TS_execute_ternary(gcv, curitem + 1, in_phrase);
			if (val2 == GIN_FALSE)
				return GIN_FALSE;
			if (val1 == GIN_TRUE && val2 == GIN_TRUE)
				return GIN_TRUE;
			else
				return GIN_MAYBE;

		case OP_OR:
			val1 = TS_execute_ternary(gcv, curitem + curitem->qoperator.left,
									  in_phrase);
			if (val1 == GIN_TRUE)
				return GIN_TRUE;
			val2 = TS_execute_ternary(gcv, curitem + 1, in_phrase);
			if (val2 == GIN_TRUE)
				return GIN_TRUE;
			if (val1 == GIN_FALSE && val2 == GIN_FALSE)
				return GIN_FALSE;
			else
				return GIN_MAYBE;

		default:
			elog(ERROR, "unrecognized operator: %d", curitem->qoperator.oper);
	}

	/* not reachable, but keep compiler quiet */
	return false;
}