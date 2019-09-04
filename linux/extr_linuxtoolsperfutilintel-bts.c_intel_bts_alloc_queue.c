#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_bts_queue {unsigned int queue_nr; int pid; int tid; int cpu; struct intel_bts* bts; } ;
struct intel_bts {int dummy; } ;

/* Variables and functions */
 struct intel_bts_queue* zalloc (int) ; 

__attribute__((used)) static struct intel_bts_queue *intel_bts_alloc_queue(struct intel_bts *bts,
						     unsigned int queue_nr)
{
	struct intel_bts_queue *btsq;

	btsq = zalloc(sizeof(struct intel_bts_queue));
	if (!btsq)
		return NULL;

	btsq->bts = bts;
	btsq->queue_nr = queue_nr;
	btsq->pid = -1;
	btsq->tid = -1;
	btsq->cpu = -1;

	return btsq;
}