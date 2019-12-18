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
struct dst_entry {TYPE_2__* lwtstate; } ;
struct TYPE_3__ {scalar_t__ prog; } ;
struct bpf_lwt {TYPE_1__ in; } ;
struct TYPE_4__ {int (* orig_input ) (struct sk_buff*) ;} ;

/* Variables and functions */
 int BPF_LWT_REROUTE ; 
 int EINVAL ; 
 int /*<<< orphan*/  NO_REDIRECT ; 
 int bpf_lwt_input_reroute (struct sk_buff*) ; 
 struct bpf_lwt* bpf_lwt_lwtunnel (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int run_lwt_bpf (struct sk_buff*,TYPE_1__*,struct dst_entry*,int /*<<< orphan*/ ) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bpf_input(struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);
	struct bpf_lwt *bpf;
	int ret;

	bpf = bpf_lwt_lwtunnel(dst->lwtstate);
	if (bpf->in.prog) {
		ret = run_lwt_bpf(skb, &bpf->in, dst, NO_REDIRECT);
		if (ret < 0)
			return ret;
		if (ret == BPF_LWT_REROUTE)
			return bpf_lwt_input_reroute(skb);
	}

	if (unlikely(!dst->lwtstate->orig_input)) {
		kfree_skb(skb);
		return -EINVAL;
	}

	return dst->lwtstate->orig_input(skb);
}