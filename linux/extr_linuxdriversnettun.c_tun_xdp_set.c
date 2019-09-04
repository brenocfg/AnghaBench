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
struct tun_struct {int /*<<< orphan*/  xdp_prog; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 struct tun_struct* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct bpf_prog*) ; 
 struct bpf_prog* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tun_xdp_set(struct net_device *dev, struct bpf_prog *prog,
		       struct netlink_ext_ack *extack)
{
	struct tun_struct *tun = netdev_priv(dev);
	struct bpf_prog *old_prog;

	old_prog = rtnl_dereference(tun->xdp_prog);
	rcu_assign_pointer(tun->xdp_prog, prog);
	if (old_prog)
		bpf_prog_put(old_prog);

	return 0;
}