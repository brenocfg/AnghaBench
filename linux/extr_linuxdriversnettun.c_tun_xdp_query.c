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
typedef  int /*<<< orphan*/  u32 ;
struct tun_struct {int /*<<< orphan*/  xdp_prog; } ;
struct net_device {int dummy; } ;
struct bpf_prog {TYPE_1__* aux; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 struct tun_struct* netdev_priv (struct net_device*) ; 
 struct bpf_prog* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 tun_xdp_query(struct net_device *dev)
{
	struct tun_struct *tun = netdev_priv(dev);
	const struct bpf_prog *xdp_prog;

	xdp_prog = rtnl_dereference(tun->xdp_prog);
	if (xdp_prog)
		return xdp_prog->aux->id;

	return 0;
}