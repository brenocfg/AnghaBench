#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct netlink_callback {TYPE_2__* nlh; } ;
struct batadv_hard_iface {TYPE_1__* net_dev; } ;
struct batadv_bla_backbone_gw {int /*<<< orphan*/  vid; int /*<<< orphan*/  orig; scalar_t__ lasttime; int /*<<< orphan*/  crc_lock; int /*<<< orphan*/  crc; } ;
struct TYPE_4__ {int /*<<< orphan*/  nlmsg_seq; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ATTR_BLA_BACKBONE ; 
 int /*<<< orphan*/  BATADV_ATTR_BLA_CRC ; 
 int /*<<< orphan*/  BATADV_ATTR_BLA_OWN ; 
 int /*<<< orphan*/  BATADV_ATTR_BLA_VID ; 
 int /*<<< orphan*/  BATADV_ATTR_LAST_SEEN_MSECS ; 
 int /*<<< orphan*/  BATADV_CMD_GET_BLA_BACKBONE ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int batadv_compare_eth (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_netlink_family ; 
 int /*<<< orphan*/  genl_dump_check_consistent (struct netlink_callback*,void*) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int jiffies_to_msecs (scalar_t__) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
batadv_bla_backbone_dump_entry(struct sk_buff *msg, u32 portid,
			       struct netlink_callback *cb,
			       struct batadv_hard_iface *primary_if,
			       struct batadv_bla_backbone_gw *backbone_gw)
{
	u8 *primary_addr = primary_if->net_dev->dev_addr;
	u16 backbone_crc;
	bool is_own;
	int msecs;
	void *hdr;
	int ret = -EINVAL;

	hdr = genlmsg_put(msg, portid, cb->nlh->nlmsg_seq,
			  &batadv_netlink_family, NLM_F_MULTI,
			  BATADV_CMD_GET_BLA_BACKBONE);
	if (!hdr) {
		ret = -ENOBUFS;
		goto out;
	}

	genl_dump_check_consistent(cb, hdr);

	is_own = batadv_compare_eth(backbone_gw->orig, primary_addr);

	spin_lock_bh(&backbone_gw->crc_lock);
	backbone_crc = backbone_gw->crc;
	spin_unlock_bh(&backbone_gw->crc_lock);

	msecs = jiffies_to_msecs(jiffies - backbone_gw->lasttime);

	if (is_own)
		if (nla_put_flag(msg, BATADV_ATTR_BLA_OWN)) {
			genlmsg_cancel(msg, hdr);
			goto out;
		}

	if (nla_put(msg, BATADV_ATTR_BLA_BACKBONE, ETH_ALEN,
		    backbone_gw->orig) ||
	    nla_put_u16(msg, BATADV_ATTR_BLA_VID, backbone_gw->vid) ||
	    nla_put_u16(msg, BATADV_ATTR_BLA_CRC,
			backbone_crc) ||
	    nla_put_u32(msg, BATADV_ATTR_LAST_SEEN_MSECS, msecs)) {
		genlmsg_cancel(msg, hdr);
		goto out;
	}

	genlmsg_end(msg, hdr);
	ret = 0;

out:
	return ret;
}