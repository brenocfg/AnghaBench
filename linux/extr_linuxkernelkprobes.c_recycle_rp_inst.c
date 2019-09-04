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
struct kretprobe_instance {int /*<<< orphan*/  hlist; struct kretprobe* rp; } ;
struct hlist_head {int dummy; } ;
struct kretprobe {int /*<<< orphan*/  lock; struct hlist_head free_instances; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (struct kretprobe*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

void recycle_rp_inst(struct kretprobe_instance *ri,
		     struct hlist_head *head)
{
	struct kretprobe *rp = ri->rp;

	/* remove rp inst off the rprobe_inst_table */
	hlist_del(&ri->hlist);
	INIT_HLIST_NODE(&ri->hlist);
	if (likely(rp)) {
		raw_spin_lock(&rp->lock);
		hlist_add_head(&ri->hlist, &rp->free_instances);
		raw_spin_unlock(&rp->lock);
	} else
		/* Unregistering */
		hlist_add_head(&ri->hlist, head);
}