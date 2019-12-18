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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_5__ {int nchild; struct TYPE_5__** child; TYPE_1__* valnode; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_2__ QTNode ;

/* Variables and functions */
 scalar_t__ QI_VAL ; 
 int /*<<< orphan*/  check_stack_depth () ; 

void
QTNClearFlags(QTNode *in, uint32 flags)
{
	/* since this function recurses, it could be driven to stack overflow. */
	check_stack_depth();

	in->flags &= ~flags;

	if (in->valnode->type != QI_VAL)
	{
		int			i;

		for (i = 0; i < in->nchild; i++)
			QTNClearFlags(in->child[i], flags);
	}
}