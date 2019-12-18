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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; int /*<<< orphan*/  name; } ;
struct ieee802154_llsec_seclevel {scalar_t__ frame_type; scalar_t__ sec_levels; scalar_t__ device_override; scalar_t__ cmd_frame_id; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IEEE802154_ATTR_DEV_INDEX ; 
 int /*<<< orphan*/  IEEE802154_ATTR_DEV_NAME ; 
 int /*<<< orphan*/  IEEE802154_ATTR_LLSEC_CMD_FRAME_ID ; 
 int /*<<< orphan*/  IEEE802154_ATTR_LLSEC_DEV_OVERRIDE ; 
 int /*<<< orphan*/  IEEE802154_ATTR_LLSEC_FRAME_TYPE ; 
 int /*<<< orphan*/  IEEE802154_ATTR_LLSEC_SECLEVELS ; 
 scalar_t__ IEEE802154_FC_TYPE_MAC_CMD ; 
 int /*<<< orphan*/  IEEE802154_LLSEC_LIST_SECLEVEL ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl802154_family ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
ieee802154_nl_fill_seclevel(struct sk_buff *msg, u32 portid, u32 seq,
			    const struct ieee802154_llsec_seclevel *sl,
			    const struct net_device *dev)
{
	void *hdr;

	hdr = genlmsg_put(msg, 0, seq, &nl802154_family, NLM_F_MULTI,
			  IEEE802154_LLSEC_LIST_SECLEVEL);
	if (!hdr)
		goto out;

	if (nla_put_string(msg, IEEE802154_ATTR_DEV_NAME, dev->name) ||
	    nla_put_u32(msg, IEEE802154_ATTR_DEV_INDEX, dev->ifindex) ||
	    nla_put_u8(msg, IEEE802154_ATTR_LLSEC_FRAME_TYPE, sl->frame_type) ||
	    nla_put_u8(msg, IEEE802154_ATTR_LLSEC_SECLEVELS, sl->sec_levels) ||
	    nla_put_u8(msg, IEEE802154_ATTR_LLSEC_DEV_OVERRIDE,
		       sl->device_override))
		goto nla_put_failure;

	if (sl->frame_type == IEEE802154_FC_TYPE_MAC_CMD &&
	    nla_put_u8(msg, IEEE802154_ATTR_LLSEC_CMD_FRAME_ID,
		       sl->cmd_frame_id))
		goto nla_put_failure;

	genlmsg_end(msg, hdr);
	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
out:
	return -EMSGSIZE;
}