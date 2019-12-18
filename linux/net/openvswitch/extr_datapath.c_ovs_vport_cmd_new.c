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
typedef  int u32 ;
struct vport_parms {int port_no; struct nlattr* upcall_portids; struct datapath* dp; struct nlattr* options; void* type; int /*<<< orphan*/  name; } ;
struct vport {int /*<<< orphan*/  dev; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct ovs_header {int /*<<< orphan*/  dp_ifindex; } ;
struct nlattr {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; struct ovs_header* userhdr; struct nlattr** attrs; } ;
struct datapath {unsigned int max_headroom; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DP_MAX_PORTS ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EFBIG ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct vport*) ; 
 size_t OVS_VPORT_ATTR_IFINDEX ; 
 size_t OVS_VPORT_ATTR_NAME ; 
 size_t OVS_VPORT_ATTR_OPTIONS ; 
 size_t OVS_VPORT_ATTR_PORT_NO ; 
 size_t OVS_VPORT_ATTR_TYPE ; 
 size_t OVS_VPORT_ATTR_UPCALL_PID ; 
 int /*<<< orphan*/  OVS_VPORT_CMD_NEW ; 
 int PTR_ERR (struct vport*) ; 
 int /*<<< orphan*/  dp_vport_genl_family ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 struct datapath* get_dp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 unsigned int netdev_get_fwd_headroom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_set_rx_headroom (int /*<<< orphan*/ ,unsigned int) ; 
 struct vport* new_vport (struct vport_parms*) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  ovs_lock () ; 
 int /*<<< orphan*/  ovs_notify (int /*<<< orphan*/ *,struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  ovs_unlock () ; 
 int /*<<< orphan*/  ovs_update_headroom (struct datapath*,unsigned int) ; 
 struct sk_buff* ovs_vport_cmd_alloc_info () ; 
 int ovs_vport_cmd_fill_info (struct vport*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vport* ovs_vport_ovsl (struct datapath*,int) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovs_vport_cmd_new(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **a = info->attrs;
	struct ovs_header *ovs_header = info->userhdr;
	struct vport_parms parms;
	struct sk_buff *reply;
	struct vport *vport;
	struct datapath *dp;
	unsigned int new_headroom;
	u32 port_no;
	int err;

	if (!a[OVS_VPORT_ATTR_NAME] || !a[OVS_VPORT_ATTR_TYPE] ||
	    !a[OVS_VPORT_ATTR_UPCALL_PID])
		return -EINVAL;
	if (a[OVS_VPORT_ATTR_IFINDEX])
		return -EOPNOTSUPP;

	port_no = a[OVS_VPORT_ATTR_PORT_NO]
		? nla_get_u32(a[OVS_VPORT_ATTR_PORT_NO]) : 0;
	if (port_no >= DP_MAX_PORTS)
		return -EFBIG;

	reply = ovs_vport_cmd_alloc_info();
	if (!reply)
		return -ENOMEM;

	ovs_lock();
restart:
	dp = get_dp(sock_net(skb->sk), ovs_header->dp_ifindex);
	err = -ENODEV;
	if (!dp)
		goto exit_unlock_free;

	if (port_no) {
		vport = ovs_vport_ovsl(dp, port_no);
		err = -EBUSY;
		if (vport)
			goto exit_unlock_free;
	} else {
		for (port_no = 1; ; port_no++) {
			if (port_no >= DP_MAX_PORTS) {
				err = -EFBIG;
				goto exit_unlock_free;
			}
			vport = ovs_vport_ovsl(dp, port_no);
			if (!vport)
				break;
		}
	}

	parms.name = nla_data(a[OVS_VPORT_ATTR_NAME]);
	parms.type = nla_get_u32(a[OVS_VPORT_ATTR_TYPE]);
	parms.options = a[OVS_VPORT_ATTR_OPTIONS];
	parms.dp = dp;
	parms.port_no = port_no;
	parms.upcall_portids = a[OVS_VPORT_ATTR_UPCALL_PID];

	vport = new_vport(&parms);
	err = PTR_ERR(vport);
	if (IS_ERR(vport)) {
		if (err == -EAGAIN)
			goto restart;
		goto exit_unlock_free;
	}

	err = ovs_vport_cmd_fill_info(vport, reply, genl_info_net(info),
				      info->snd_portid, info->snd_seq, 0,
				      OVS_VPORT_CMD_NEW, GFP_KERNEL);

	new_headroom = netdev_get_fwd_headroom(vport->dev);

	if (new_headroom > dp->max_headroom)
		ovs_update_headroom(dp, new_headroom);
	else
		netdev_set_rx_headroom(vport->dev, dp->max_headroom);

	BUG_ON(err < 0);
	ovs_unlock();

	ovs_notify(&dp_vport_genl_family, reply, info);
	return 0;

exit_unlock_free:
	ovs_unlock();
	kfree_skb(reply);
	return err;
}