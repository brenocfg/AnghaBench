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
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/  len; } ;
struct bpf_prog {int dummy; } ;
struct bpf_dtab_netdev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_xdp_tx (struct sk_buff*,struct bpf_prog*) ; 
 scalar_t__ unlikely (int) ; 
 int xdp_ok_fwd_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dev_map_generic_redirect(struct bpf_dtab_netdev *dst, struct sk_buff *skb,
			     struct bpf_prog *xdp_prog)
{
	int err;

	err = xdp_ok_fwd_dev(dst->dev, skb->len);
	if (unlikely(err))
		return err;
	skb->dev = dst->dev;
	generic_xdp_tx(skb, xdp_prog);

	return 0;
}