#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct scm_request {int /*<<< orphan*/  list; TYPE_1__* aob; scalar_t__* request; } ;
struct msb {int flags; scalar_t__ data_addr; } ;
struct TYPE_2__ {struct msb* msb; } ;

/* Variables and functions */
 scalar_t__ IS_ALIGNED (scalar_t__,int /*<<< orphan*/ ) ; 
 int MSB_FLAG_IDA ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  aidaw_pool ; 
 int /*<<< orphan*/  inactive_requests ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  mempool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nr_requests_per_io ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virt_to_page (scalar_t__) ; 

__attribute__((used)) static void scm_request_done(struct scm_request *scmrq)
{
	unsigned long flags;
	struct msb *msb;
	u64 aidaw;
	int i;

	for (i = 0; i < nr_requests_per_io && scmrq->request[i]; i++) {
		msb = &scmrq->aob->msb[i];
		aidaw = msb->data_addr;

		if ((msb->flags & MSB_FLAG_IDA) && aidaw &&
		    IS_ALIGNED(aidaw, PAGE_SIZE))
			mempool_free(virt_to_page(aidaw), aidaw_pool);
	}

	spin_lock_irqsave(&list_lock, flags);
	list_add(&scmrq->list, &inactive_requests);
	spin_unlock_irqrestore(&list_lock, flags);
}