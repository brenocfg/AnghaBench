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
typedef  int u32 ;
struct xdp_buff {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int XDP_DROP ; 
 int XDP_PASS ; 
#define  XDP_REDIRECT 129 
#define  XDP_TX 128 
 int /*<<< orphan*/  generic_xdp_tx (struct sk_buff*,struct bpf_prog*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int netif_receive_generic_xdp (struct sk_buff*,struct xdp_buff*,struct bpf_prog*) ; 
 int xdp_do_generic_redirect (int /*<<< orphan*/ ,struct sk_buff*,struct xdp_buff*,struct bpf_prog*) ; 

int do_xdp_generic(struct bpf_prog *xdp_prog, struct sk_buff *skb)
{
	if (xdp_prog) {
		struct xdp_buff xdp;
		u32 act;
		int err;

		act = netif_receive_generic_xdp(skb, &xdp, xdp_prog);
		if (act != XDP_PASS) {
			switch (act) {
			case XDP_REDIRECT:
				err = xdp_do_generic_redirect(skb->dev, skb,
							      &xdp, xdp_prog);
				if (err)
					goto out_redir;
				break;
			case XDP_TX:
				generic_xdp_tx(skb, xdp_prog);
				break;
			}
			return XDP_DROP;
		}
	}
	return XDP_PASS;
out_redir:
	kfree_skb(skb);
	return XDP_DROP;
}