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
struct xdp_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct bpf_redirect_info {int /*<<< orphan*/  map; } ;
struct bpf_prog {int dummy; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 struct bpf_map* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_redirect_info ; 
 scalar_t__ likely (struct bpf_map*) ; 
 struct bpf_redirect_info* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int xdp_do_redirect_map (struct net_device*,struct xdp_buff*,struct bpf_prog*,struct bpf_map*,struct bpf_redirect_info*) ; 
 int xdp_do_redirect_slow (struct net_device*,struct xdp_buff*,struct bpf_prog*,struct bpf_redirect_info*) ; 

int xdp_do_redirect(struct net_device *dev, struct xdp_buff *xdp,
		    struct bpf_prog *xdp_prog)
{
	struct bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);
	struct bpf_map *map = READ_ONCE(ri->map);

	if (likely(map))
		return xdp_do_redirect_map(dev, xdp, xdp_prog, map, ri);

	return xdp_do_redirect_slow(dev, xdp, xdp_prog, ri);
}