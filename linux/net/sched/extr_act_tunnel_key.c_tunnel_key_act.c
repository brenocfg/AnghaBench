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
struct tcf_tunnel_key_params {int tcft_action; TYPE_2__* tcft_enc_metadata; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpu_bstats; } ;
struct tcf_tunnel_key {int /*<<< orphan*/  tcf_action; TYPE_1__ common; int /*<<< orphan*/  tcf_tm; int /*<<< orphan*/  params; } ;
struct tcf_result {int dummy; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
#define  TCA_TUNNEL_KEY_ACT_RELEASE 129 
#define  TCA_TUNNEL_KEY_ACT_SET 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  bstats_cpu_update (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  dst_clone (int /*<<< orphan*/ *) ; 
 struct tcf_tunnel_key_params* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_lastuse_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 
 struct tcf_tunnel_key* to_tunnel_key (struct tc_action const*) ; 

__attribute__((used)) static int tunnel_key_act(struct sk_buff *skb, const struct tc_action *a,
			  struct tcf_result *res)
{
	struct tcf_tunnel_key *t = to_tunnel_key(a);
	struct tcf_tunnel_key_params *params;
	int action;

	params = rcu_dereference_bh(t->params);

	tcf_lastuse_update(&t->tcf_tm);
	bstats_cpu_update(this_cpu_ptr(t->common.cpu_bstats), skb);
	action = READ_ONCE(t->tcf_action);

	switch (params->tcft_action) {
	case TCA_TUNNEL_KEY_ACT_RELEASE:
		skb_dst_drop(skb);
		break;
	case TCA_TUNNEL_KEY_ACT_SET:
		skb_dst_drop(skb);
		skb_dst_set(skb, dst_clone(&params->tcft_enc_metadata->dst));
		break;
	default:
		WARN_ONCE(1, "Bad tunnel_key action %d.\n",
			  params->tcft_action);
		break;
	}

	return action;
}