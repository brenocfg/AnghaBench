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
struct vport {scalar_t__ port_no; int /*<<< orphan*/  dev; struct datapath* dp; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlattr {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; int /*<<< orphan*/  userhdr; struct nlattr** attrs; } ;
struct datapath {scalar_t__ max_headroom; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct vport*) ; 
 scalar_t__ OVSP_LOCAL ; 
 int /*<<< orphan*/  OVS_VPORT_CMD_DEL ; 
 int PTR_ERR (struct vport*) ; 
 int /*<<< orphan*/  dp_vport_genl_family ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct vport* lookup_vport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlattr**) ; 
 scalar_t__ netdev_get_fwd_headroom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_reset_rx_headroom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_dp_detach_port (struct vport*) ; 
 int /*<<< orphan*/  ovs_lock () ; 
 int /*<<< orphan*/  ovs_notify (int /*<<< orphan*/ *,struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  ovs_unlock () ; 
 struct sk_buff* ovs_vport_cmd_alloc_info () ; 
 int ovs_vport_cmd_fill_info (struct vport*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_headroom (struct datapath*) ; 

__attribute__((used)) static int ovs_vport_cmd_del(struct sk_buff *skb, struct genl_info *info)
{
	bool must_update_headroom = false;
	struct nlattr **a = info->attrs;
	struct sk_buff *reply;
	struct datapath *dp;
	struct vport *vport;
	int err;

	reply = ovs_vport_cmd_alloc_info();
	if (!reply)
		return -ENOMEM;

	ovs_lock();
	vport = lookup_vport(sock_net(skb->sk), info->userhdr, a);
	err = PTR_ERR(vport);
	if (IS_ERR(vport))
		goto exit_unlock_free;

	if (vport->port_no == OVSP_LOCAL) {
		err = -EINVAL;
		goto exit_unlock_free;
	}

	err = ovs_vport_cmd_fill_info(vport, reply, genl_info_net(info),
				      info->snd_portid, info->snd_seq, 0,
				      OVS_VPORT_CMD_DEL);
	BUG_ON(err < 0);

	/* the vport deletion may trigger dp headroom update */
	dp = vport->dp;
	if (netdev_get_fwd_headroom(vport->dev) == dp->max_headroom)
		must_update_headroom = true;
	netdev_reset_rx_headroom(vport->dev);
	ovs_dp_detach_port(vport);

	if (must_update_headroom)
		update_headroom(dp);
	ovs_unlock();

	ovs_notify(&dp_vport_genl_family, reply, info);
	return 0;

exit_unlock_free:
	ovs_unlock();
	kfree_skb(reply);
	return err;
}