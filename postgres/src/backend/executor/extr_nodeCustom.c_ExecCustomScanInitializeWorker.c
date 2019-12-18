#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  (* InitializeWorkerCustomScan ) (TYPE_5__*,int /*<<< orphan*/ ,void*) ;} ;
struct TYPE_11__ {TYPE_1__* plan; } ;
struct TYPE_12__ {TYPE_2__ ps; } ;
struct TYPE_14__ {TYPE_3__ ss; TYPE_6__* methods; } ;
struct TYPE_13__ {int /*<<< orphan*/  toc; } ;
struct TYPE_10__ {int plan_node_id; } ;
typedef  TYPE_4__ ParallelWorkerContext ;
typedef  TYPE_5__ CustomScanState ;
typedef  TYPE_6__ CustomExecMethods ;

/* Variables and functions */
 void* shm_toc_lookup (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ,void*) ; 

void
ExecCustomScanInitializeWorker(CustomScanState *node,
							   ParallelWorkerContext *pwcxt)
{
	const CustomExecMethods *methods = node->methods;

	if (methods->InitializeWorkerCustomScan)
	{
		int			plan_node_id = node->ss.ps.plan->plan_node_id;
		void	   *coordinate;

		coordinate = shm_toc_lookup(pwcxt->toc, plan_node_id, false);
		methods->InitializeWorkerCustomScan(node, pwcxt->toc, coordinate);
	}
}