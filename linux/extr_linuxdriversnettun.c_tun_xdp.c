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
struct netdev_bpf {int command; int /*<<< orphan*/  prog_id; int /*<<< orphan*/  extack; int /*<<< orphan*/  prog; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  XDP_QUERY_PROG 129 
#define  XDP_SETUP_PROG 128 
 int /*<<< orphan*/  tun_xdp_query (struct net_device*) ; 
 int tun_xdp_set (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tun_xdp(struct net_device *dev, struct netdev_bpf *xdp)
{
	switch (xdp->command) {
	case XDP_SETUP_PROG:
		return tun_xdp_set(dev, xdp->prog, xdp->extack);
	case XDP_QUERY_PROG:
		xdp->prog_id = tun_xdp_query(dev);
		return 0;
	default:
		return -EINVAL;
	}
}