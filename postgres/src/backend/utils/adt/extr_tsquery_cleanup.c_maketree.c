#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* left; struct TYPE_8__* right; TYPE_2__* valnode; } ;
struct TYPE_6__ {scalar_t__ oper; int left; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_1__ qoperator; } ;
typedef  TYPE_2__ QueryItem ;
typedef  TYPE_3__ NODE ;

/* Variables and functions */
 scalar_t__ OP_NOT ; 
 scalar_t__ QI_OPR ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static NODE *
maketree(QueryItem *in)
{
	NODE	   *node = (NODE *) palloc(sizeof(NODE));

	/* since this function recurses, it could be driven to stack overflow. */
	check_stack_depth();

	node->valnode = in;
	node->right = node->left = NULL;
	if (in->type == QI_OPR)
	{
		node->right = maketree(in + 1);
		if (in->qoperator.oper != OP_NOT)
			node->left = maketree(in + in->qoperator.left);
	}
	return node;
}