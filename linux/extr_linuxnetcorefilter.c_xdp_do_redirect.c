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
struct net_device {int dummy; } ;
struct bpf_redirect_info {scalar_t__ ifindex; int /*<<< orphan*/  map; } ;
struct bpf_prog {int dummy; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct bpf_map* READ_ONCE (int /*<<< orphan*/ ) ; 
 int __bpf_tx_xdp (struct net_device*,int /*<<< orphan*/ *,struct xdp_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _trace_xdp_redirect (struct net_device*,struct bpf_prog*,scalar_t__) ; 
 int /*<<< orphan*/  _trace_xdp_redirect_err (struct net_device*,struct bpf_prog*,scalar_t__,int) ; 
 int /*<<< orphan*/  bpf_redirect_info ; 
 struct net_device* dev_get_by_index_rcu (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct bpf_redirect_info* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int xdp_do_redirect_map (struct net_device*,struct xdp_buff*,struct bpf_prog*,struct bpf_map*) ; 

int xdp_do_redirect(struct net_device *dev, struct xdp_buff *xdp,
		    struct bpf_prog *xdp_prog)
{
	struct bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);
	struct bpf_map *map = READ_ONCE(ri->map);
	struct net_device *fwd;
	u32 index = ri->ifindex;
	int err;

	if (map)
		return xdp_do_redirect_map(dev, xdp, xdp_prog, map);

	fwd = dev_get_by_index_rcu(dev_net(dev), index);
	ri->ifindex = 0;
	if (unlikely(!fwd)) {
		err = -EINVAL;
		goto err;
	}

	err = __bpf_tx_xdp(fwd, NULL, xdp, 0);
	if (unlikely(err))
		goto err;

	_trace_xdp_redirect(dev, xdp_prog, index);
	return 0;
err:
	_trace_xdp_redirect_err(dev, xdp_prog, index, err);
	return err;
}