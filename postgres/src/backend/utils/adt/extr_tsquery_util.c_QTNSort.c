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
struct TYPE_7__ {int nchild; struct TYPE_7__** child; TYPE_2__* valnode; } ;
struct TYPE_5__ {scalar_t__ oper; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ qoperator; } ;
typedef  TYPE_3__ QTNode ;

/* Variables and functions */
 scalar_t__ OP_PHRASE ; 
 scalar_t__ QI_OPR ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  cmpQTN ; 
 int /*<<< orphan*/  qsort (void*,int,int,int /*<<< orphan*/ ) ; 

void
QTNSort(QTNode *in)
{
	int			i;

	/* since this function recurses, it could be driven to stack overflow. */
	check_stack_depth();

	if (in->valnode->type != QI_OPR)
		return;

	for (i = 0; i < in->nchild; i++)
		QTNSort(in->child[i]);
	if (in->nchild > 1 && in->valnode->qoperator.oper != OP_PHRASE)
		qsort((void *) in->child, in->nchild, sizeof(QTNode *), cmpQTN);
}