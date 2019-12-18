#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_5__ {int oper; int /*<<< orphan*/  left; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ qoperator; } ;
typedef  int (* TSExecuteCallback ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  QueryOperand ;
typedef  TYPE_2__ QueryItem ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  OP_AND 131 
#define  OP_NOT 130 
#define  OP_OR 129 
#define  OP_PHRASE 128 
 scalar_t__ QI_VAL ; 
 int TS_EXEC_CALC_NOT ; 
 int TS_phrase_execute (TYPE_2__*,void*,int,int (*) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

bool
TS_execute(QueryItem *curitem, void *arg, uint32 flags,
		   TSExecuteCallback chkcond)
{
	/* since this function recurses, it could be driven to stack overflow */
	check_stack_depth();

	if (curitem->type == QI_VAL)
		return chkcond(arg, (QueryOperand *) curitem,
					   NULL /* we don't need position info */ );

	switch (curitem->qoperator.oper)
	{
		case OP_NOT:
			if (flags & TS_EXEC_CALC_NOT)
				return !TS_execute(curitem + 1, arg, flags, chkcond);
			else
				return true;

		case OP_AND:
			if (TS_execute(curitem + curitem->qoperator.left, arg, flags, chkcond))
				return TS_execute(curitem + 1, arg, flags, chkcond);
			else
				return false;

		case OP_OR:
			if (TS_execute(curitem + curitem->qoperator.left, arg, flags, chkcond))
				return true;
			else
				return TS_execute(curitem + 1, arg, flags, chkcond);

		case OP_PHRASE:
			return TS_phrase_execute(curitem, arg, flags, chkcond, NULL);

		default:
			elog(ERROR, "unrecognized operator: %d", curitem->qoperator.oper);
	}

	/* not reachable, but keep compiler quiet */
	return false;
}