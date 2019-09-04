#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nsim_bpf_bound_prog {char* state; } ;
struct netdevsim {int /*<<< orphan*/  bpf_map_accept; int /*<<< orphan*/  xdp_hw; int /*<<< orphan*/  xdp; int /*<<< orphan*/  bpf_bind_accept; } ;
struct TYPE_9__ {TYPE_5__* prog; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  prog; } ;
struct netdev_bpf {int command; int /*<<< orphan*/  offmap; TYPE_4__ offload; TYPE_1__ verifier; } ;
struct net_device {int dummy; } ;
struct TYPE_10__ {TYPE_3__* aux; } ;
struct TYPE_8__ {TYPE_2__* offload; } ;
struct TYPE_7__ {struct nsim_bpf_bound_prog* dev_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
#define  BPF_OFFLOAD_DESTROY 136 
#define  BPF_OFFLOAD_MAP_ALLOC 135 
#define  BPF_OFFLOAD_MAP_FREE 134 
#define  BPF_OFFLOAD_TRANSLATE 133 
#define  BPF_OFFLOAD_VERIFIER_PREP 132 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  XDP_QUERY_PROG 131 
#define  XDP_QUERY_PROG_HW 130 
#define  XDP_SETUP_PROG 129 
#define  XDP_SETUP_PROG_HW 128 
 struct netdevsim* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nsim_bpf_analyzer_ops ; 
 int nsim_bpf_create_prog (struct netdevsim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsim_bpf_destroy_prog (TYPE_5__*) ; 
 int nsim_bpf_map_alloc (struct netdevsim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsim_bpf_map_free (int /*<<< orphan*/ ) ; 
 int nsim_setup_prog_checks (struct netdevsim*,struct netdev_bpf*) ; 
 int nsim_setup_prog_hw_checks (struct netdevsim*,struct netdev_bpf*) ; 
 int nsim_xdp_set_prog (struct netdevsim*,struct netdev_bpf*,int /*<<< orphan*/ *) ; 
 int xdp_attachment_query (int /*<<< orphan*/ *,struct netdev_bpf*) ; 

int nsim_bpf(struct net_device *dev, struct netdev_bpf *bpf)
{
	struct netdevsim *ns = netdev_priv(dev);
	struct nsim_bpf_bound_prog *state;
	int err;

	ASSERT_RTNL();

	switch (bpf->command) {
	case BPF_OFFLOAD_VERIFIER_PREP:
		if (!ns->bpf_bind_accept)
			return -EOPNOTSUPP;

		err = nsim_bpf_create_prog(ns, bpf->verifier.prog);
		if (err)
			return err;

		bpf->verifier.ops = &nsim_bpf_analyzer_ops;
		return 0;
	case BPF_OFFLOAD_TRANSLATE:
		state = bpf->offload.prog->aux->offload->dev_priv;

		state->state = "xlated";
		return 0;
	case BPF_OFFLOAD_DESTROY:
		nsim_bpf_destroy_prog(bpf->offload.prog);
		return 0;
	case XDP_QUERY_PROG:
		return xdp_attachment_query(&ns->xdp, bpf);
	case XDP_QUERY_PROG_HW:
		return xdp_attachment_query(&ns->xdp_hw, bpf);
	case XDP_SETUP_PROG:
		err = nsim_setup_prog_checks(ns, bpf);
		if (err)
			return err;

		return nsim_xdp_set_prog(ns, bpf, &ns->xdp);
	case XDP_SETUP_PROG_HW:
		err = nsim_setup_prog_hw_checks(ns, bpf);
		if (err)
			return err;

		return nsim_xdp_set_prog(ns, bpf, &ns->xdp_hw);
	case BPF_OFFLOAD_MAP_ALLOC:
		if (!ns->bpf_map_accept)
			return -EOPNOTSUPP;

		return nsim_bpf_map_alloc(ns, bpf->offmap);
	case BPF_OFFLOAD_MAP_FREE:
		nsim_bpf_map_free(bpf->offmap);
		return 0;
	default:
		return -EINVAL;
	}
}