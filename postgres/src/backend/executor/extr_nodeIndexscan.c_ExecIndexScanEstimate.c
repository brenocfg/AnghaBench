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
struct TYPE_12__ {int /*<<< orphan*/  es_snapshot; } ;
struct TYPE_8__ {TYPE_5__* state; } ;
struct TYPE_9__ {TYPE_1__ ps; } ;
struct TYPE_11__ {int /*<<< orphan*/  iss_PscanLen; int /*<<< orphan*/  iss_RelationDesc; TYPE_2__ ss; } ;
struct TYPE_10__ {int /*<<< orphan*/  estimator; } ;
typedef  TYPE_3__ ParallelContext ;
typedef  TYPE_4__ IndexScanState ;
typedef  TYPE_5__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  index_parallelscan_estimate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_toc_estimate_chunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_toc_estimate_keys (int /*<<< orphan*/ *,int) ; 

void
ExecIndexScanEstimate(IndexScanState *node,
					  ParallelContext *pcxt)
{
	EState	   *estate = node->ss.ps.state;

	node->iss_PscanLen = index_parallelscan_estimate(node->iss_RelationDesc,
													 estate->es_snapshot);
	shm_toc_estimate_chunk(&pcxt->estimator, node->iss_PscanLen);
	shm_toc_estimate_keys(&pcxt->estimator, 1);
}