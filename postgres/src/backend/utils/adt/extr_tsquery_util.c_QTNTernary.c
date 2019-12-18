#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ oper; } ;
struct TYPE_11__ {scalar_t__ type; int nchild; int flags; struct TYPE_11__* valnode; struct TYPE_11__** child; TYPE_1__ qoperator; } ;
typedef  TYPE_2__ QTNode ;

/* Variables and functions */
 scalar_t__ OP_AND ; 
 scalar_t__ OP_OR ; 
 scalar_t__ QI_OPR ; 
 int QTN_NEEDFREE ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  memcpy (TYPE_2__**,TYPE_2__**,int) ; 
 int /*<<< orphan*/  memmove (TYPE_2__**,TYPE_2__**,int) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 
 scalar_t__ repalloc (TYPE_2__**,int) ; 

void
QTNTernary(QTNode *in)
{
	int			i;

	/* since this function recurses, it could be driven to stack overflow. */
	check_stack_depth();

	if (in->valnode->type != QI_OPR)
		return;

	for (i = 0; i < in->nchild; i++)
		QTNTernary(in->child[i]);

	/* Only AND and OR are associative, so don't flatten other node types */
	if (in->valnode->qoperator.oper != OP_AND &&
		in->valnode->qoperator.oper != OP_OR)
		return;

	for (i = 0; i < in->nchild; i++)
	{
		QTNode	   *cc = in->child[i];

		if (cc->valnode->type == QI_OPR &&
			in->valnode->qoperator.oper == cc->valnode->qoperator.oper)
		{
			int			oldnchild = in->nchild;

			in->nchild += cc->nchild - 1;
			in->child = (QTNode **) repalloc(in->child, in->nchild * sizeof(QTNode *));

			if (i + 1 != oldnchild)
				memmove(in->child + i + cc->nchild, in->child + i + 1,
						(oldnchild - i - 1) * sizeof(QTNode *));

			memcpy(in->child + i, cc->child, cc->nchild * sizeof(QTNode *));
			i += cc->nchild - 1;

			if (cc->flags & QTN_NEEDFREE)
				pfree(cc->valnode);
			pfree(cc);
		}
	}
}