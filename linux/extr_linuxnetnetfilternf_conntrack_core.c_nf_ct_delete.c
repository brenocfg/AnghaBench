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
typedef  int /*<<< orphan*/  u32 ;
struct nf_conn_tstamp {scalar_t__ stop; } ;
struct nf_conn {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPCT_DESTROY ; 
 int /*<<< orphan*/  IPS_DYING_BIT ; 
 scalar_t__ ktime_get_real_ns () ; 
 struct nf_conn_tstamp* nf_conn_tstamp_find (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_conntrack_ecache_delayed_work (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_conntrack_ecache_work (int /*<<< orphan*/ ) ; 
 scalar_t__ nf_conntrack_event_report (int /*<<< orphan*/ ,struct nf_conn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_ct_delete_from_lists (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_net (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool nf_ct_delete(struct nf_conn *ct, u32 portid, int report)
{
	struct nf_conn_tstamp *tstamp;

	if (test_and_set_bit(IPS_DYING_BIT, &ct->status))
		return false;

	tstamp = nf_conn_tstamp_find(ct);
	if (tstamp && tstamp->stop == 0)
		tstamp->stop = ktime_get_real_ns();

	if (nf_conntrack_event_report(IPCT_DESTROY, ct,
				    portid, report) < 0) {
		/* destroy event was not delivered. nf_ct_put will
		 * be done by event cache worker on redelivery.
		 */
		nf_ct_delete_from_lists(ct);
		nf_conntrack_ecache_delayed_work(nf_ct_net(ct));
		return false;
	}

	nf_conntrack_ecache_work(nf_ct_net(ct));
	nf_ct_delete_from_lists(ct);
	nf_ct_put(ct);
	return true;
}