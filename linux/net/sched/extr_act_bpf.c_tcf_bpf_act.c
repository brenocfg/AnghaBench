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
struct tcf_result {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_qstats; int /*<<< orphan*/  cpu_bstats; } ;
struct tcf_bpf {int tcf_action; TYPE_1__ common; int /*<<< orphan*/  filter; int /*<<< orphan*/  tcf_tm; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  mac_len; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int BPF_PROG_RUN (struct bpf_prog*,struct sk_buff*) ; 
#define  TC_ACT_OK 133 
#define  TC_ACT_PIPE 132 
#define  TC_ACT_RECLASSIFY 131 
#define  TC_ACT_REDIRECT 130 
#define  TC_ACT_SHOT 129 
#define  TC_ACT_UNSPEC 128 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_compute_data_pointers (struct sk_buff*) ; 
 int /*<<< orphan*/  bstats_cpu_update (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  qstats_drop_inc (int /*<<< orphan*/ ) ; 
 struct bpf_prog* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int skb_at_tc_ingress (struct sk_buff*) ; 
 int /*<<< orphan*/  tcf_lastuse_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 
 struct tcf_bpf* to_bpf (struct tc_action const*) ; 

__attribute__((used)) static int tcf_bpf_act(struct sk_buff *skb, const struct tc_action *act,
		       struct tcf_result *res)
{
	bool at_ingress = skb_at_tc_ingress(skb);
	struct tcf_bpf *prog = to_bpf(act);
	struct bpf_prog *filter;
	int action, filter_res;

	tcf_lastuse_update(&prog->tcf_tm);
	bstats_cpu_update(this_cpu_ptr(prog->common.cpu_bstats), skb);

	rcu_read_lock();
	filter = rcu_dereference(prog->filter);
	if (at_ingress) {
		__skb_push(skb, skb->mac_len);
		bpf_compute_data_pointers(skb);
		filter_res = BPF_PROG_RUN(filter, skb);
		__skb_pull(skb, skb->mac_len);
	} else {
		bpf_compute_data_pointers(skb);
		filter_res = BPF_PROG_RUN(filter, skb);
	}
	rcu_read_unlock();

	/* A BPF program may overwrite the default action opcode.
	 * Similarly as in cls_bpf, if filter_res == -1 we use the
	 * default action specified from tc.
	 *
	 * In case a different well-known TC_ACT opcode has been
	 * returned, it will overwrite the default one.
	 *
	 * For everything else that is unkown, TC_ACT_UNSPEC is
	 * returned.
	 */
	switch (filter_res) {
	case TC_ACT_PIPE:
	case TC_ACT_RECLASSIFY:
	case TC_ACT_OK:
	case TC_ACT_REDIRECT:
		action = filter_res;
		break;
	case TC_ACT_SHOT:
		action = filter_res;
		qstats_drop_inc(this_cpu_ptr(prog->common.cpu_qstats));
		break;
	case TC_ACT_UNSPEC:
		action = prog->tcf_action;
		break;
	default:
		action = TC_ACT_UNSPEC;
		break;
	}

	return action;
}