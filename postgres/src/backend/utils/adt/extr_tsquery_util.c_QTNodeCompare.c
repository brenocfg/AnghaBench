#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ nchild; TYPE_1__* valnode; int /*<<< orphan*/  word; struct TYPE_10__** child; } ;
struct TYPE_9__ {scalar_t__ valcrc; int /*<<< orphan*/  length; } ;
struct TYPE_8__ {scalar_t__ oper; scalar_t__ distance; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_3__ qoperand; TYPE_2__ qoperator; } ;
typedef  TYPE_2__ QueryOperator ;
typedef  TYPE_3__ QueryOperand ;
typedef  TYPE_4__ QTNode ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ OP_PHRASE ; 
 scalar_t__ QI_OPR ; 
 scalar_t__ QI_VAL ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int tsCompareString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
QTNodeCompare(QTNode *an, QTNode *bn)
{
	/* since this function recurses, it could be driven to stack overflow. */
	check_stack_depth();

	if (an->valnode->type != bn->valnode->type)
		return (an->valnode->type > bn->valnode->type) ? -1 : 1;

	if (an->valnode->type == QI_OPR)
	{
		QueryOperator *ao = &an->valnode->qoperator;
		QueryOperator *bo = &bn->valnode->qoperator;

		if (ao->oper != bo->oper)
			return (ao->oper > bo->oper) ? -1 : 1;

		if (an->nchild != bn->nchild)
			return (an->nchild > bn->nchild) ? -1 : 1;

		{
			int			i,
						res;

			for (i = 0; i < an->nchild; i++)
				if ((res = QTNodeCompare(an->child[i], bn->child[i])) != 0)
					return res;
		}

		if (ao->oper == OP_PHRASE && ao->distance != bo->distance)
			return (ao->distance > bo->distance) ? -1 : 1;

		return 0;
	}
	else if (an->valnode->type == QI_VAL)
	{
		QueryOperand *ao = &an->valnode->qoperand;
		QueryOperand *bo = &bn->valnode->qoperand;

		if (ao->valcrc != bo->valcrc)
		{
			return (ao->valcrc > bo->valcrc) ? -1 : 1;
		}

		return tsCompareString(an->word, ao->length, bn->word, bo->length, false);
	}
	else
	{
		elog(ERROR, "unrecognized QueryItem type: %d", an->valnode->type);
		return 0;				/* keep compiler quiet */
	}
}