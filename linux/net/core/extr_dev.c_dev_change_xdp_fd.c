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
typedef  scalar_t__ u32 ;
struct netlink_ext_ack {int dummy; } ;
struct net_device_ops {scalar_t__ ndo_bpf; } ;
struct net_device {struct net_device_ops* netdev_ops; } ;
struct bpf_prog {TYPE_1__* aux; } ;
typedef  enum bpf_netdev_command { ____Placeholder_bpf_netdev_command } bpf_netdev_command ;
typedef  scalar_t__ bpf_op_t ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_XDP ; 
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int PTR_ERR (struct bpf_prog*) ; 
 scalar_t__ XDP_FLAGS_DRV_MODE ; 
 scalar_t__ XDP_FLAGS_HW_MODE ; 
 scalar_t__ XDP_FLAGS_SKB_MODE ; 
 scalar_t__ XDP_FLAGS_UPDATE_IF_NOEXIST ; 
 int XDP_QUERY_PROG ; 
 int XDP_QUERY_PROG_HW ; 
 scalar_t__ __dev_xdp_query (struct net_device*,scalar_t__,int) ; 
 struct bpf_prog* bpf_prog_get_type_dev (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bpf_prog_is_dev_bound (TYPE_1__*) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 int dev_xdp_install (struct net_device*,scalar_t__,struct netlink_ext_ack*,scalar_t__,struct bpf_prog*) ; 
 scalar_t__ generic_xdp_install ; 

int dev_change_xdp_fd(struct net_device *dev, struct netlink_ext_ack *extack,
		      int fd, u32 flags)
{
	const struct net_device_ops *ops = dev->netdev_ops;
	enum bpf_netdev_command query;
	struct bpf_prog *prog = NULL;
	bpf_op_t bpf_op, bpf_chk;
	bool offload;
	int err;

	ASSERT_RTNL();

	offload = flags & XDP_FLAGS_HW_MODE;
	query = offload ? XDP_QUERY_PROG_HW : XDP_QUERY_PROG;

	bpf_op = bpf_chk = ops->ndo_bpf;
	if (!bpf_op && (flags & (XDP_FLAGS_DRV_MODE | XDP_FLAGS_HW_MODE))) {
		NL_SET_ERR_MSG(extack, "underlying driver does not support XDP in native mode");
		return -EOPNOTSUPP;
	}
	if (!bpf_op || (flags & XDP_FLAGS_SKB_MODE))
		bpf_op = generic_xdp_install;
	if (bpf_op == bpf_chk)
		bpf_chk = generic_xdp_install;

	if (fd >= 0) {
		u32 prog_id;

		if (!offload && __dev_xdp_query(dev, bpf_chk, XDP_QUERY_PROG)) {
			NL_SET_ERR_MSG(extack, "native and generic XDP can't be active at the same time");
			return -EEXIST;
		}

		prog_id = __dev_xdp_query(dev, bpf_op, query);
		if ((flags & XDP_FLAGS_UPDATE_IF_NOEXIST) && prog_id) {
			NL_SET_ERR_MSG(extack, "XDP program already attached");
			return -EBUSY;
		}

		prog = bpf_prog_get_type_dev(fd, BPF_PROG_TYPE_XDP,
					     bpf_op == ops->ndo_bpf);
		if (IS_ERR(prog))
			return PTR_ERR(prog);

		if (!offload && bpf_prog_is_dev_bound(prog->aux)) {
			NL_SET_ERR_MSG(extack, "using device-bound program without HW_MODE flag is not supported");
			bpf_prog_put(prog);
			return -EINVAL;
		}

		/* prog->aux->id may be 0 for orphaned device-bound progs */
		if (prog->aux->id && prog->aux->id == prog_id) {
			bpf_prog_put(prog);
			return 0;
		}
	} else {
		if (!__dev_xdp_query(dev, bpf_op, query))
			return 0;
	}

	err = dev_xdp_install(dev, bpf_op, extack, flags, prog);
	if (err < 0 && prog)
		bpf_prog_put(prog);

	return err;
}