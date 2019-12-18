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
typedef  int /*<<< orphan*/  upcall ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vport {int /*<<< orphan*/  dev; } ;
struct sw_flow_key {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct dp_upcall_info {int actions_len; struct nlattr const* actions; int /*<<< orphan*/  egress_tun_info; int /*<<< orphan*/  portid; struct nlattr const* userdata; int /*<<< orphan*/  mru; int /*<<< orphan*/  cmd; } ;
struct datapath {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mru; } ;

/* Variables and functions */
 TYPE_1__* OVS_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  OVS_PACKET_CMD_ACTION ; 
#define  OVS_USERSPACE_ATTR_ACTIONS 131 
#define  OVS_USERSPACE_ATTR_EGRESS_TUN_PORT 130 
#define  OVS_USERSPACE_ATTR_PID 129 
#define  OVS_USERSPACE_ATTR_USERDATA 128 
 int dev_fill_metadata_dst (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct dp_upcall_info*,int /*<<< orphan*/ ,int) ; 
 struct nlattr* nla_data (struct nlattr const*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr const*) ; 
 int nla_len (struct nlattr const*) ; 
 struct nlattr* nla_next (struct nlattr const*,int*) ; 
 int nla_type (struct nlattr const*) ; 
 int ovs_dp_upcall (struct datapath*,struct sk_buff*,struct sw_flow_key*,struct dp_upcall_info*,int /*<<< orphan*/ ) ; 
 struct vport* ovs_vport_rcu (struct datapath*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tunnel_info (struct sk_buff*) ; 

__attribute__((used)) static int output_userspace(struct datapath *dp, struct sk_buff *skb,
			    struct sw_flow_key *key, const struct nlattr *attr,
			    const struct nlattr *actions, int actions_len,
			    uint32_t cutlen)
{
	struct dp_upcall_info upcall;
	const struct nlattr *a;
	int rem;

	memset(&upcall, 0, sizeof(upcall));
	upcall.cmd = OVS_PACKET_CMD_ACTION;
	upcall.mru = OVS_CB(skb)->mru;

	for (a = nla_data(attr), rem = nla_len(attr); rem > 0;
		 a = nla_next(a, &rem)) {
		switch (nla_type(a)) {
		case OVS_USERSPACE_ATTR_USERDATA:
			upcall.userdata = a;
			break;

		case OVS_USERSPACE_ATTR_PID:
			upcall.portid = nla_get_u32(a);
			break;

		case OVS_USERSPACE_ATTR_EGRESS_TUN_PORT: {
			/* Get out tunnel info. */
			struct vport *vport;

			vport = ovs_vport_rcu(dp, nla_get_u32(a));
			if (vport) {
				int err;

				err = dev_fill_metadata_dst(vport->dev, skb);
				if (!err)
					upcall.egress_tun_info = skb_tunnel_info(skb);
			}

			break;
		}

		case OVS_USERSPACE_ATTR_ACTIONS: {
			/* Include actions. */
			upcall.actions = actions;
			upcall.actions_len = actions_len;
			break;
		}

		} /* End of switch. */
	}

	return ovs_dp_upcall(dp, skb, key, &upcall, cutlen);
}