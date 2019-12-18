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
typedef  unsigned int uint32 ;
struct TYPE_10__ {unsigned int sign; int nchild; char* word; struct TYPE_10__** child; TYPE_3__* valnode; } ;
struct TYPE_8__ {int distance; scalar_t__ valcrc; } ;
struct TYPE_7__ {scalar_t__ oper; int left; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_2__ qoperand; TYPE_1__ qoperator; } ;
typedef  TYPE_3__ QueryItem ;
typedef  TYPE_4__ QTNode ;

/* Variables and functions */
 scalar_t__ OP_NOT ; 
 scalar_t__ QI_OPR ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 scalar_t__ palloc0 (int) ; 

QTNode *
QT2QTN(QueryItem *in, char *operand)
{
	QTNode	   *node = (QTNode *) palloc0(sizeof(QTNode));

	/* since this function recurses, it could be driven to stack overflow. */
	check_stack_depth();

	node->valnode = in;

	if (in->type == QI_OPR)
	{
		node->child = (QTNode **) palloc0(sizeof(QTNode *) * 2);
		node->child[0] = QT2QTN(in + 1, operand);
		node->sign = node->child[0]->sign;
		if (in->qoperator.oper == OP_NOT)
			node->nchild = 1;
		else
		{
			node->nchild = 2;
			node->child[1] = QT2QTN(in + in->qoperator.left, operand);
			node->sign |= node->child[1]->sign;
		}
	}
	else if (operand)
	{
		node->word = operand + in->qoperand.distance;
		node->sign = ((uint32) 1) << (((unsigned int) in->qoperand.valcrc) % 32);
	}

	return node;
}