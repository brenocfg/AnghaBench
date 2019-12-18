#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cpu_bstats; } ;
struct tcf_sample {int rate; int trunc_size; scalar_t__ truncate; int /*<<< orphan*/  psample_group; int /*<<< orphan*/  tcf_action; TYPE_1__ common; int /*<<< orphan*/  tcf_tm; } ;
struct tcf_result {int dummy; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int skb_iif; int len; int /*<<< orphan*/  mac_len; TYPE_2__* dev; } ;
struct psample_group {int dummy; } ;
struct TYPE_4__ {int ifindex; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstats_cpu_update (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int prandom_u32 () ; 
 int /*<<< orphan*/  psample_sample_packet (struct psample_group*,struct sk_buff*,int,int,int,int) ; 
 struct psample_group* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_at_tc_ingress (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_lastuse_update (int /*<<< orphan*/ *) ; 
 scalar_t__ tcf_sample_dev_ok_push (TYPE_2__*) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 
 struct tcf_sample* to_sample (struct tc_action const*) ; 

__attribute__((used)) static int tcf_sample_act(struct sk_buff *skb, const struct tc_action *a,
			  struct tcf_result *res)
{
	struct tcf_sample *s = to_sample(a);
	struct psample_group *psample_group;
	int retval;
	int size;
	int iif;
	int oif;

	tcf_lastuse_update(&s->tcf_tm);
	bstats_cpu_update(this_cpu_ptr(s->common.cpu_bstats), skb);
	retval = READ_ONCE(s->tcf_action);

	psample_group = rcu_dereference_bh(s->psample_group);

	/* randomly sample packets according to rate */
	if (psample_group && (prandom_u32() % s->rate == 0)) {
		if (!skb_at_tc_ingress(skb)) {
			iif = skb->skb_iif;
			oif = skb->dev->ifindex;
		} else {
			iif = skb->dev->ifindex;
			oif = 0;
		}

		/* on ingress, the mac header gets popped, so push it back */
		if (skb_at_tc_ingress(skb) && tcf_sample_dev_ok_push(skb->dev))
			skb_push(skb, skb->mac_len);

		size = s->truncate ? s->trunc_size : skb->len;
		psample_sample_packet(psample_group, skb, size, iif, oif,
				      s->rate);

		if (skb_at_tc_ingress(skb) && tcf_sample_dev_ok_push(skb->dev))
			skb_pull(skb, skb->mac_len);
	}

	return retval;
}