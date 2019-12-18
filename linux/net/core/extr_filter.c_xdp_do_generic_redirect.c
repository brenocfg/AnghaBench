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
typedef  scalar_t__ u32 ;
struct xdp_buff {int dummy; } ;
struct sk_buff {struct net_device* dev; int /*<<< orphan*/  len; } ;
struct net_device {int dummy; } ;
struct bpf_redirect_info {scalar_t__ tgt_index; int /*<<< orphan*/  map; } ;
struct bpf_prog {int dummy; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct bpf_map* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _trace_xdp_redirect (struct net_device*,struct bpf_prog*,scalar_t__) ; 
 int /*<<< orphan*/  _trace_xdp_redirect_err (struct net_device*,struct bpf_prog*,scalar_t__,int) ; 
 int /*<<< orphan*/  bpf_redirect_info ; 
 struct net_device* dev_get_by_index_rcu (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  generic_xdp_tx (struct sk_buff*,struct bpf_prog*) ; 
 struct bpf_redirect_info* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int xdp_do_generic_redirect_map (struct net_device*,struct sk_buff*,struct xdp_buff*,struct bpf_prog*,struct bpf_map*) ; 
 int xdp_ok_fwd_dev (struct net_device*,int /*<<< orphan*/ ) ; 

int xdp_do_generic_redirect(struct net_device *dev, struct sk_buff *skb,
			    struct xdp_buff *xdp, struct bpf_prog *xdp_prog)
{
	struct bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);
	struct bpf_map *map = READ_ONCE(ri->map);
	u32 index = ri->tgt_index;
	struct net_device *fwd;
	int err = 0;

	if (map)
		return xdp_do_generic_redirect_map(dev, skb, xdp, xdp_prog,
						   map);
	ri->tgt_index = 0;
	fwd = dev_get_by_index_rcu(dev_net(dev), index);
	if (unlikely(!fwd)) {
		err = -EINVAL;
		goto err;
	}

	err = xdp_ok_fwd_dev(fwd, skb->len);
	if (unlikely(err))
		goto err;

	skb->dev = fwd;
	_trace_xdp_redirect(dev, xdp_prog, index);
	generic_xdp_tx(skb, xdp_prog);
	return 0;
err:
	_trace_xdp_redirect_err(dev, xdp_prog, index, err);
	return err;
}