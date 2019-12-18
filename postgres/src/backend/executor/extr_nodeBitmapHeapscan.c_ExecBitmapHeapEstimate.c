#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* state; } ;
struct TYPE_9__ {TYPE_1__ ps; } ;
struct TYPE_12__ {int /*<<< orphan*/  pscan_len; TYPE_2__ ss; } ;
struct TYPE_11__ {int /*<<< orphan*/  es_snapshot; } ;
struct TYPE_10__ {int /*<<< orphan*/  estimator; } ;
typedef  TYPE_3__ ParallelContext ;
typedef  TYPE_4__ EState ;
typedef  TYPE_5__ BitmapHeapScanState ;

/* Variables and functions */
 int /*<<< orphan*/  EstimateSnapshotSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ParallelBitmapHeapState ; 
 int /*<<< orphan*/  add_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phs_snapshot_data ; 
 int /*<<< orphan*/  shm_toc_estimate_chunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_toc_estimate_keys (int /*<<< orphan*/ *,int) ; 

void
ExecBitmapHeapEstimate(BitmapHeapScanState *node,
					   ParallelContext *pcxt)
{
	EState	   *estate = node->ss.ps.state;

	node->pscan_len = add_size(offsetof(ParallelBitmapHeapState,
										phs_snapshot_data),
							   EstimateSnapshotSpace(estate->es_snapshot));

	shm_toc_estimate_chunk(&pcxt->estimator, node->pscan_len);
	shm_toc_estimate_keys(&pcxt->estimator, 1);
}