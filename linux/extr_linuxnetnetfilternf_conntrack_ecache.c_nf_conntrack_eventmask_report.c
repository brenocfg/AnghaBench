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
typedef  scalar_t__ u32 ;
struct nf_ct_event_notifier {int (* fcn ) (unsigned int,struct nf_ct_event*) ;} ;
struct nf_ct_event {scalar_t__ portid; int report; struct nf_conn* ct; } ;
struct nf_conntrack_ecache {scalar_t__ portid; unsigned long missed; unsigned int ctmask; int /*<<< orphan*/  state; } ;
struct nf_conn {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  nf_conntrack_event_cb; } ;
struct net {TYPE_1__ ct; } ;

/* Variables and functions */
 int IPCT_DESTROY ; 
 int /*<<< orphan*/  NFCT_ECACHE_DESTROY_FAIL ; 
 struct nf_conntrack_ecache* nf_ct_ecache_find (struct nf_conn*) ; 
 scalar_t__ nf_ct_is_confirmed (struct nf_conn*) ; 
 struct net* nf_ct_net (struct nf_conn*) ; 
 struct nf_ct_event_notifier* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (unsigned int,struct nf_ct_event*) ; 
 scalar_t__ unlikely (int) ; 

int nf_conntrack_eventmask_report(unsigned int eventmask, struct nf_conn *ct,
				  u32 portid, int report)
{
	int ret = 0;
	struct net *net = nf_ct_net(ct);
	struct nf_ct_event_notifier *notify;
	struct nf_conntrack_ecache *e;

	rcu_read_lock();
	notify = rcu_dereference(net->ct.nf_conntrack_event_cb);
	if (!notify)
		goto out_unlock;

	e = nf_ct_ecache_find(ct);
	if (!e)
		goto out_unlock;

	if (nf_ct_is_confirmed(ct)) {
		struct nf_ct_event item = {
			.ct	= ct,
			.portid	= e->portid ? e->portid : portid,
			.report = report
		};
		/* This is a resent of a destroy event? If so, skip missed */
		unsigned long missed = e->portid ? 0 : e->missed;

		if (!((eventmask | missed) & e->ctmask))
			goto out_unlock;

		ret = notify->fcn(eventmask | missed, &item);
		if (unlikely(ret < 0 || missed)) {
			spin_lock_bh(&ct->lock);
			if (ret < 0) {
				/* This is a destroy event that has been
				 * triggered by a process, we store the PORTID
				 * to include it in the retransmission.
				 */
				if (eventmask & (1 << IPCT_DESTROY)) {
					if (e->portid == 0 && portid != 0)
						e->portid = portid;
					e->state = NFCT_ECACHE_DESTROY_FAIL;
				} else {
					e->missed |= eventmask;
				}
			} else {
				e->missed &= ~missed;
			}
			spin_unlock_bh(&ct->lock);
		}
	}
out_unlock:
	rcu_read_unlock();
	return ret;
}