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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct dst_entry {int /*<<< orphan*/  lwtstate; } ;
struct TYPE_2__ {scalar_t__ prog; } ;
struct bpf_lwt {TYPE_1__ xmit; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  BPF_LWT_REROUTE 130 
#define  BPF_OK 129 
#define  BPF_REDIRECT 128 
 int /*<<< orphan*/  CAN_REDIRECT ; 
 int EINVAL ; 
 int LWTUNNEL_XMIT_CONTINUE ; 
 int LWTUNNEL_XMIT_DONE ; 
 struct bpf_lwt* bpf_lwt_lwtunnel (int /*<<< orphan*/ ) ; 
 int bpf_lwt_xmit_reroute (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int run_lwt_bpf (struct sk_buff*,TYPE_1__*,struct dst_entry*,int /*<<< orphan*/ ) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int xmit_check_hhlen (struct sk_buff*) ; 

__attribute__((used)) static int bpf_xmit(struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);
	struct bpf_lwt *bpf;

	bpf = bpf_lwt_lwtunnel(dst->lwtstate);
	if (bpf->xmit.prog) {
		__be16 proto = skb->protocol;
		int ret;

		ret = run_lwt_bpf(skb, &bpf->xmit, dst, CAN_REDIRECT);
		switch (ret) {
		case BPF_OK:
			/* If the header changed, e.g. via bpf_lwt_push_encap,
			 * BPF_LWT_REROUTE below should have been used if the
			 * protocol was also changed.
			 */
			if (skb->protocol != proto) {
				kfree_skb(skb);
				return -EINVAL;
			}
			/* If the header was expanded, headroom might be too
			 * small for L2 header to come, expand as needed.
			 */
			ret = xmit_check_hhlen(skb);
			if (unlikely(ret))
				return ret;

			return LWTUNNEL_XMIT_CONTINUE;
		case BPF_REDIRECT:
			return LWTUNNEL_XMIT_DONE;
		case BPF_LWT_REROUTE:
			return bpf_lwt_xmit_reroute(skb);
		default:
			return ret;
		}
	}

	return LWTUNNEL_XMIT_CONTINUE;
}