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
typedef  int uint32 ;
struct TYPE_4__ {scalar_t__ oper; int left; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ qoperator; } ;
typedef  TYPE_1__ QueryOperator ;
typedef  TYPE_2__ QueryItem ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ OP_AND ; 
 scalar_t__ OP_NOT ; 
 scalar_t__ OP_OR ; 
 scalar_t__ OP_PHRASE ; 
 scalar_t__ QI_OPR ; 
 scalar_t__ QI_VAL ; 
 scalar_t__ QI_VALSTOP ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
findoprnd_recurse(QueryItem *ptr, uint32 *pos, int nnodes, bool *needcleanup)
{
	/* since this function recurses, it could be driven to stack overflow. */
	check_stack_depth();

	if (*pos >= nnodes)
		elog(ERROR, "malformed tsquery: operand not found");

	if (ptr[*pos].type == QI_VAL)
	{
		(*pos)++;
	}
	else if (ptr[*pos].type == QI_VALSTOP)
	{
		*needcleanup = true;	/* we'll have to remove stop words */
		(*pos)++;
	}
	else
	{
		Assert(ptr[*pos].type == QI_OPR);

		if (ptr[*pos].qoperator.oper == OP_NOT)
		{
			ptr[*pos].qoperator.left = 1;	/* fixed offset */
			(*pos)++;

			/* process the only argument */
			findoprnd_recurse(ptr, pos, nnodes, needcleanup);
		}
		else
		{
			QueryOperator *curitem = &ptr[*pos].qoperator;
			int			tmp = *pos; /* save current position */

			Assert(curitem->oper == OP_AND ||
				   curitem->oper == OP_OR ||
				   curitem->oper == OP_PHRASE);

			(*pos)++;

			/* process RIGHT argument */
			findoprnd_recurse(ptr, pos, nnodes, needcleanup);

			curitem->left = *pos - tmp; /* set LEFT arg's offset */

			/* process LEFT argument */
			findoprnd_recurse(ptr, pos, nnodes, needcleanup);
		}
	}
}