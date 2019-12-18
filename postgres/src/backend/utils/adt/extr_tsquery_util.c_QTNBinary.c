#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nchild; int sign; struct TYPE_7__** child; TYPE_2__* valnode; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  oper; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ qoperator; } ;
typedef  TYPE_2__ QueryItem ;
typedef  TYPE_3__ QTNode ;

/* Variables and functions */
 scalar_t__ QI_OPR ; 
 int /*<<< orphan*/  QTN_NEEDFREE ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 scalar_t__ palloc0 (int) ; 

void
QTNBinary(QTNode *in)
{
	int			i;

	/* since this function recurses, it could be driven to stack overflow. */
	check_stack_depth();

	if (in->valnode->type != QI_OPR)
		return;

	for (i = 0; i < in->nchild; i++)
		QTNBinary(in->child[i]);

	while (in->nchild > 2)
	{
		QTNode	   *nn = (QTNode *) palloc0(sizeof(QTNode));

		nn->valnode = (QueryItem *) palloc0(sizeof(QueryItem));
		nn->child = (QTNode **) palloc0(sizeof(QTNode *) * 2);

		nn->nchild = 2;
		nn->flags = QTN_NEEDFREE;

		nn->child[0] = in->child[0];
		nn->child[1] = in->child[1];
		nn->sign = nn->child[0]->sign | nn->child[1]->sign;

		nn->valnode->type = in->valnode->type;
		nn->valnode->qoperator.oper = in->valnode->qoperator.oper;

		in->child[0] = nn;
		in->child[1] = in->child[in->nchild - 1];
		in->nchild--;
	}
}