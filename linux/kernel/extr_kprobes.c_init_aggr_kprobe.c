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
struct kprobe {int flags; int /*<<< orphan*/  hlist; int /*<<< orphan*/  list; scalar_t__ post_handler; int /*<<< orphan*/  fault_handler; int /*<<< orphan*/  pre_handler; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int KPROBE_FLAG_OPTIMIZED ; 
 int /*<<< orphan*/  aggr_fault_handler ; 
 scalar_t__ aggr_post_handler ; 
 int /*<<< orphan*/  aggr_pre_handler ; 
 int /*<<< orphan*/  copy_kprobe (struct kprobe*,struct kprobe*) ; 
 int /*<<< orphan*/  flush_insn_slot (struct kprobe*) ; 
 int /*<<< orphan*/  hlist_replace_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kprobe_gone (struct kprobe*) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_aggr_kprobe(struct kprobe *ap, struct kprobe *p)
{
	/* Copy p's insn slot to ap */
	copy_kprobe(p, ap);
	flush_insn_slot(ap);
	ap->addr = p->addr;
	ap->flags = p->flags & ~KPROBE_FLAG_OPTIMIZED;
	ap->pre_handler = aggr_pre_handler;
	ap->fault_handler = aggr_fault_handler;
	/* We don't care the kprobe which has gone. */
	if (p->post_handler && !kprobe_gone(p))
		ap->post_handler = aggr_post_handler;

	INIT_LIST_HEAD(&ap->list);
	INIT_HLIST_NODE(&ap->hlist);

	list_add_rcu(&p->list, &ap->list);
	hlist_replace_rcu(&p->hlist, &ap->hlist);
}