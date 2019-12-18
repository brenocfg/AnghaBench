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
struct tcf_result {int ingress; int /*<<< orphan*/  qstats; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_qstats; int /*<<< orphan*/  cpu_bstats; } ;
struct tcf_mirred {TYPE_1__ common; int /*<<< orphan*/  tcfm_dev; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcfm_eaction; int /*<<< orphan*/  tcfm_mac_header_xmit; int /*<<< orphan*/  tcf_tm; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int tc_redirected; scalar_t__ tstamp; scalar_t__ tc_from_ingress; scalar_t__ tc_at_ingress; struct net_device* dev; int /*<<< orphan*/  skb_iif; int /*<<< orphan*/  mac_len; } ;
struct net_device {int flags; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_UP ; 
 unsigned int MIRRED_RECURSION_LIMIT ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int TC_ACT_CONSUMED ; 
 int TC_ACT_SHOT ; 
 int /*<<< orphan*/  __this_cpu_dec (int /*<<< orphan*/ ) ; 
 unsigned int __this_cpu_inc_return (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstats_cpu_update (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  mirred_rec_level ; 
 int /*<<< orphan*/  net_notice_ratelimited (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_name (struct net_device*) ; 
 int netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_notice_once (char*) ; 
 int /*<<< orphan*/  qstats_overlimit_inc (int /*<<< orphan*/ ) ; 
 struct net_device* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int skb_at_tc_ingress (struct sk_buff*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_mac_header (struct sk_buff*) ; 
 int skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull_rcsum (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push_rcsum (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tc_reinsert (struct sk_buff*,struct tcf_result*) ; 
 int /*<<< orphan*/  tcf_lastuse_update (int /*<<< orphan*/ *) ; 
 int tcf_mirred_act_wants_ingress (int) ; 
 scalar_t__ tcf_mirred_can_reinsert (int) ; 
 int tcf_mirred_is_act_redirect (int) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 
 struct tcf_mirred* to_mirred (struct tc_action const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcf_mirred_act(struct sk_buff *skb, const struct tc_action *a,
			  struct tcf_result *res)
{
	struct tcf_mirred *m = to_mirred(a);
	struct sk_buff *skb2 = skb;
	bool m_mac_header_xmit;
	struct net_device *dev;
	unsigned int rec_level;
	int retval, err = 0;
	bool use_reinsert;
	bool want_ingress;
	bool is_redirect;
	int m_eaction;
	int mac_len;

	rec_level = __this_cpu_inc_return(mirred_rec_level);
	if (unlikely(rec_level > MIRRED_RECURSION_LIMIT)) {
		net_warn_ratelimited("Packet exceeded mirred recursion limit on dev %s\n",
				     netdev_name(skb->dev));
		__this_cpu_dec(mirred_rec_level);
		return TC_ACT_SHOT;
	}

	tcf_lastuse_update(&m->tcf_tm);
	bstats_cpu_update(this_cpu_ptr(m->common.cpu_bstats), skb);

	m_mac_header_xmit = READ_ONCE(m->tcfm_mac_header_xmit);
	m_eaction = READ_ONCE(m->tcfm_eaction);
	retval = READ_ONCE(m->tcf_action);
	dev = rcu_dereference_bh(m->tcfm_dev);
	if (unlikely(!dev)) {
		pr_notice_once("tc mirred: target device is gone\n");
		goto out;
	}

	if (unlikely(!(dev->flags & IFF_UP))) {
		net_notice_ratelimited("tc mirred to Houston: device %s is down\n",
				       dev->name);
		goto out;
	}

	/* we could easily avoid the clone only if called by ingress and clsact;
	 * since we can't easily detect the clsact caller, skip clone only for
	 * ingress - that covers the TC S/W datapath.
	 */
	is_redirect = tcf_mirred_is_act_redirect(m_eaction);
	use_reinsert = skb_at_tc_ingress(skb) && is_redirect &&
		       tcf_mirred_can_reinsert(retval);
	if (!use_reinsert) {
		skb2 = skb_clone(skb, GFP_ATOMIC);
		if (!skb2)
			goto out;
	}

	/* If action's target direction differs than filter's direction,
	 * and devices expect a mac header on xmit, then mac push/pull is
	 * needed.
	 */
	want_ingress = tcf_mirred_act_wants_ingress(m_eaction);
	if (skb_at_tc_ingress(skb) != want_ingress && m_mac_header_xmit) {
		if (!skb_at_tc_ingress(skb)) {
			/* caught at egress, act ingress: pull mac */
			mac_len = skb_network_header(skb) - skb_mac_header(skb);
			skb_pull_rcsum(skb2, mac_len);
		} else {
			/* caught at ingress, act egress: push mac */
			skb_push_rcsum(skb2, skb->mac_len);
		}
	}

	skb2->skb_iif = skb->dev->ifindex;
	skb2->dev = dev;

	/* mirror is always swallowed */
	if (is_redirect) {
		skb2->tc_redirected = 1;
		skb2->tc_from_ingress = skb2->tc_at_ingress;
		if (skb2->tc_from_ingress)
			skb2->tstamp = 0;
		/* let's the caller reinsert the packet, if possible */
		if (use_reinsert) {
			res->ingress = want_ingress;
			res->qstats = this_cpu_ptr(m->common.cpu_qstats);
			skb_tc_reinsert(skb, res);
			__this_cpu_dec(mirred_rec_level);
			return TC_ACT_CONSUMED;
		}
	}

	if (!want_ingress)
		err = dev_queue_xmit(skb2);
	else
		err = netif_receive_skb(skb2);

	if (err) {
out:
		qstats_overlimit_inc(this_cpu_ptr(m->common.cpu_qstats));
		if (tcf_mirred_is_act_redirect(m_eaction))
			retval = TC_ACT_SHOT;
	}
	__this_cpu_dec(mirred_rec_level);

	return retval;
}