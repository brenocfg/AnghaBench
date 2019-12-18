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
struct vport {struct datapath* dp; } ;
struct sk_buff {int dummy; } ;
struct datapath {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  OVS_VPORT_CMD_DEL ; 
 int /*<<< orphan*/  PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dp_vport_genl_family ; 
 int /*<<< orphan*/  genl_set_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_multicast_netns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_dp_detach_port (struct vport*) ; 
 int /*<<< orphan*/  ovs_dp_get_net (struct datapath*) ; 
 struct sk_buff* ovs_vport_cmd_build_info (struct vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dp_detach_port_notify(struct vport *vport)
{
	struct sk_buff *notify;
	struct datapath *dp;

	dp = vport->dp;
	notify = ovs_vport_cmd_build_info(vport, ovs_dp_get_net(dp),
					  0, 0, OVS_VPORT_CMD_DEL);
	ovs_dp_detach_port(vport);
	if (IS_ERR(notify)) {
		genl_set_err(&dp_vport_genl_family, ovs_dp_get_net(dp), 0,
			     0, PTR_ERR(notify));
		return;
	}

	genlmsg_multicast_netns(&dp_vport_genl_family,
				ovs_dp_get_net(dp), notify, 0,
				0, GFP_KERNEL);
}