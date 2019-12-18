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
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  prog; } ;
struct seg6_local_lwt {TYPE_1__ bpf; } ;
struct seg6_bpf_srh_state {int hdrlen; int valid; struct ipv6_sr_hdr* srh; } ;
struct ipv6_sr_hdr {int hdrlen; } ;
struct TYPE_4__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
#define  BPF_DROP 130 
#define  BPF_OK 129 
#define  BPF_REDIRECT 128 
 int EINVAL ; 
 int /*<<< orphan*/  advance_nextseg (struct ipv6_sr_hdr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_compute_data_pointers (struct sk_buff*) ; 
 int bpf_prog_run_save_cb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int dst_input (struct sk_buff*) ; 
 struct ipv6_sr_hdr* get_and_validate_srh (struct sk_buff*) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_warn_once (char*,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  seg6_bpf_has_valid_srh (struct sk_buff*) ; 
 int /*<<< orphan*/  seg6_bpf_srh_states ; 
 int /*<<< orphan*/  seg6_lookup_nexthop (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct seg6_bpf_srh_state* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int input_action_end_bpf(struct sk_buff *skb,
				struct seg6_local_lwt *slwt)
{
	struct seg6_bpf_srh_state *srh_state =
		this_cpu_ptr(&seg6_bpf_srh_states);
	struct ipv6_sr_hdr *srh;
	int ret;

	srh = get_and_validate_srh(skb);
	if (!srh) {
		kfree_skb(skb);
		return -EINVAL;
	}
	advance_nextseg(srh, &ipv6_hdr(skb)->daddr);

	/* preempt_disable is needed to protect the per-CPU buffer srh_state,
	 * which is also accessed by the bpf_lwt_seg6_* helpers
	 */
	preempt_disable();
	srh_state->srh = srh;
	srh_state->hdrlen = srh->hdrlen << 3;
	srh_state->valid = true;

	rcu_read_lock();
	bpf_compute_data_pointers(skb);
	ret = bpf_prog_run_save_cb(slwt->bpf.prog, skb);
	rcu_read_unlock();

	switch (ret) {
	case BPF_OK:
	case BPF_REDIRECT:
		break;
	case BPF_DROP:
		goto drop;
	default:
		pr_warn_once("bpf-seg6local: Illegal return value %u\n", ret);
		goto drop;
	}

	if (srh_state->srh && !seg6_bpf_has_valid_srh(skb))
		goto drop;

	preempt_enable();
	if (ret != BPF_REDIRECT)
		seg6_lookup_nexthop(skb, NULL, 0);

	return dst_input(skb);

drop:
	preempt_enable();
	kfree_skb(skb);
	return -EINVAL;
}