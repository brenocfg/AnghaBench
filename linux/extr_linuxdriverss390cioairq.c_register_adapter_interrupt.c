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
struct airq_struct {size_t isc; int lsi_mask; int /*<<< orphan*/  list; int /*<<< orphan*/  flags; scalar_t__ lsi_ptr; int /*<<< orphan*/  handler; } ;
typedef  int /*<<< orphan*/  dbf_txt ;

/* Variables and functions */
 int /*<<< orphan*/  AIRQ_PTR_ALLOCATED ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t MAX_ISC ; 
 int /*<<< orphan*/ * airq_lists ; 
 int /*<<< orphan*/  airq_lists_lock ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_register (size_t) ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,struct airq_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int register_adapter_interrupt(struct airq_struct *airq)
{
	char dbf_txt[32];

	if (!airq->handler || airq->isc > MAX_ISC)
		return -EINVAL;
	if (!airq->lsi_ptr) {
		airq->lsi_ptr = kzalloc(1, GFP_KERNEL);
		if (!airq->lsi_ptr)
			return -ENOMEM;
		airq->flags |= AIRQ_PTR_ALLOCATED;
	}
	if (!airq->lsi_mask)
		airq->lsi_mask = 0xff;
	snprintf(dbf_txt, sizeof(dbf_txt), "rairq:%p", airq);
	CIO_TRACE_EVENT(4, dbf_txt);
	isc_register(airq->isc);
	spin_lock(&airq_lists_lock);
	hlist_add_head_rcu(&airq->list, &airq_lists[airq->isc]);
	spin_unlock(&airq_lists_lock);
	return 0;
}