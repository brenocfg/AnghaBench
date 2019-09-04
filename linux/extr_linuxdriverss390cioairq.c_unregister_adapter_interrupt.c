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
struct airq_struct {int flags; int /*<<< orphan*/ * lsi_ptr; int /*<<< orphan*/  isc; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  dbf_txt ;

/* Variables and functions */
 int AIRQ_PTR_ALLOCATED ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int /*<<< orphan*/  airq_lists_lock ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,struct airq_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void unregister_adapter_interrupt(struct airq_struct *airq)
{
	char dbf_txt[32];

	if (hlist_unhashed(&airq->list))
		return;
	snprintf(dbf_txt, sizeof(dbf_txt), "urairq:%p", airq);
	CIO_TRACE_EVENT(4, dbf_txt);
	spin_lock(&airq_lists_lock);
	hlist_del_rcu(&airq->list);
	spin_unlock(&airq_lists_lock);
	synchronize_rcu();
	isc_unregister(airq->isc);
	if (airq->flags & AIRQ_PTR_ALLOCATED) {
		kfree(airq->lsi_ptr);
		airq->lsi_ptr = NULL;
		airq->flags &= ~AIRQ_PTR_ALLOCATED;
	}
}