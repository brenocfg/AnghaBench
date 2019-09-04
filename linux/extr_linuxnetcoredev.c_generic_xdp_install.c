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
struct netdev_bpf {int command; int /*<<< orphan*/  prog_id; struct bpf_prog* prog; } ;
struct net_device {int /*<<< orphan*/  xdp_prog; } ;
struct bpf_prog {TYPE_1__* aux; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  XDP_QUERY_PROG 129 
#define  XDP_SETUP_PROG 128 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 int /*<<< orphan*/  dev_disable_gro_hw (struct net_device*) ; 
 int /*<<< orphan*/  dev_disable_lro (struct net_device*) ; 
 int /*<<< orphan*/  generic_xdp_needed_key ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct bpf_prog*) ; 
 struct bpf_prog* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_branch_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  static_branch_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int generic_xdp_install(struct net_device *dev, struct netdev_bpf *xdp)
{
	struct bpf_prog *old = rtnl_dereference(dev->xdp_prog);
	struct bpf_prog *new = xdp->prog;
	int ret = 0;

	switch (xdp->command) {
	case XDP_SETUP_PROG:
		rcu_assign_pointer(dev->xdp_prog, new);
		if (old)
			bpf_prog_put(old);

		if (old && !new) {
			static_branch_dec(&generic_xdp_needed_key);
		} else if (new && !old) {
			static_branch_inc(&generic_xdp_needed_key);
			dev_disable_lro(dev);
			dev_disable_gro_hw(dev);
		}
		break;

	case XDP_QUERY_PROG:
		xdp->prog_id = old ? old->aux->id : 0;
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}