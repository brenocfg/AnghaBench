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
struct TYPE_7__ {int /*<<< orphan*/ * chgParam; } ;
struct TYPE_9__ {int nplans; TYPE_1__ ps; TYPE_2__** bitmapplans; } ;
struct TYPE_8__ {int /*<<< orphan*/ * chgParam; } ;
typedef  TYPE_2__ PlanState ;
typedef  TYPE_3__ BitmapOrState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecReScan (TYPE_2__*) ; 
 int /*<<< orphan*/  UpdateChangedParamSet (TYPE_2__*,int /*<<< orphan*/ *) ; 

void
ExecReScanBitmapOr(BitmapOrState *node)
{
	int			i;

	for (i = 0; i < node->nplans; i++)
	{
		PlanState  *subnode = node->bitmapplans[i];

		/*
		 * ExecReScan doesn't know about my subplans, so I have to do
		 * changed-parameter signaling myself.
		 */
		if (node->ps.chgParam != NULL)
			UpdateChangedParamSet(subnode, node->ps.chgParam);

		/*
		 * If chgParam of subnode is not null then plan will be re-scanned by
		 * first ExecProcNode.
		 */
		if (subnode->chgParam == NULL)
			ExecReScan(subnode);
	}
}