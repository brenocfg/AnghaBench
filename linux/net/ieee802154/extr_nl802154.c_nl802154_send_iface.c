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
struct wpan_dev {int iftype; int /*<<< orphan*/  ackreq; int /*<<< orphan*/  lbt; int /*<<< orphan*/  min_be; int /*<<< orphan*/  csma_retries; int /*<<< orphan*/  max_be; int /*<<< orphan*/  frame_retries; int /*<<< orphan*/  pan_id; int /*<<< orphan*/  short_addr; int /*<<< orphan*/  extended_addr; struct net_device* netdev; } ;
struct sk_buff {int dummy; } ;
struct net_device {int ifindex; int /*<<< orphan*/  name; } ;
struct cfg802154_registered_device {int wpan_phy_idx; int devlist_generation; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NL802154_ATTR_ACKREQ_DEFAULT ; 
 int /*<<< orphan*/  NL802154_ATTR_EXTENDED_ADDR ; 
 int /*<<< orphan*/  NL802154_ATTR_GENERATION ; 
 int /*<<< orphan*/  NL802154_ATTR_IFINDEX ; 
 int /*<<< orphan*/  NL802154_ATTR_IFNAME ; 
 int /*<<< orphan*/  NL802154_ATTR_IFTYPE ; 
 int /*<<< orphan*/  NL802154_ATTR_LBT_MODE ; 
 int /*<<< orphan*/  NL802154_ATTR_MAX_BE ; 
 int /*<<< orphan*/  NL802154_ATTR_MAX_CSMA_BACKOFFS ; 
 int /*<<< orphan*/  NL802154_ATTR_MAX_FRAME_RETRIES ; 
 int /*<<< orphan*/  NL802154_ATTR_MIN_BE ; 
 int /*<<< orphan*/  NL802154_ATTR_PAD ; 
 int /*<<< orphan*/  NL802154_ATTR_PAN_ID ; 
 int /*<<< orphan*/  NL802154_ATTR_SHORT_ADDR ; 
 int /*<<< orphan*/  NL802154_ATTR_WPAN_DEV ; 
 int /*<<< orphan*/  NL802154_ATTR_WPAN_PHY ; 
 int /*<<< orphan*/  NL802154_CMD_NEW_INTERFACE ; 
 int cfg802154_rdev_list_generation ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 scalar_t__ nl802154_get_llsec_params (struct sk_buff*,struct cfg802154_registered_device*,struct wpan_dev*) ; 
 void* nl802154hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_le16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_le64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_s8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpan_dev_id (struct wpan_dev*) ; 

__attribute__((used)) static int
nl802154_send_iface(struct sk_buff *msg, u32 portid, u32 seq, int flags,
		    struct cfg802154_registered_device *rdev,
		    struct wpan_dev *wpan_dev)
{
	struct net_device *dev = wpan_dev->netdev;
	void *hdr;

	hdr = nl802154hdr_put(msg, portid, seq, flags,
			      NL802154_CMD_NEW_INTERFACE);
	if (!hdr)
		return -1;

	if (dev &&
	    (nla_put_u32(msg, NL802154_ATTR_IFINDEX, dev->ifindex) ||
	     nla_put_string(msg, NL802154_ATTR_IFNAME, dev->name)))
		goto nla_put_failure;

	if (nla_put_u32(msg, NL802154_ATTR_WPAN_PHY, rdev->wpan_phy_idx) ||
	    nla_put_u32(msg, NL802154_ATTR_IFTYPE, wpan_dev->iftype) ||
	    nla_put_u64_64bit(msg, NL802154_ATTR_WPAN_DEV,
			      wpan_dev_id(wpan_dev), NL802154_ATTR_PAD) ||
	    nla_put_u32(msg, NL802154_ATTR_GENERATION,
			rdev->devlist_generation ^
			(cfg802154_rdev_list_generation << 2)))
		goto nla_put_failure;

	/* address settings */
	if (nla_put_le64(msg, NL802154_ATTR_EXTENDED_ADDR,
			 wpan_dev->extended_addr,
			 NL802154_ATTR_PAD) ||
	    nla_put_le16(msg, NL802154_ATTR_SHORT_ADDR,
			 wpan_dev->short_addr) ||
	    nla_put_le16(msg, NL802154_ATTR_PAN_ID, wpan_dev->pan_id))
		goto nla_put_failure;

	/* ARET handling */
	if (nla_put_s8(msg, NL802154_ATTR_MAX_FRAME_RETRIES,
		       wpan_dev->frame_retries) ||
	    nla_put_u8(msg, NL802154_ATTR_MAX_BE, wpan_dev->max_be) ||
	    nla_put_u8(msg, NL802154_ATTR_MAX_CSMA_BACKOFFS,
		       wpan_dev->csma_retries) ||
	    nla_put_u8(msg, NL802154_ATTR_MIN_BE, wpan_dev->min_be))
		goto nla_put_failure;

	/* listen before transmit */
	if (nla_put_u8(msg, NL802154_ATTR_LBT_MODE, wpan_dev->lbt))
		goto nla_put_failure;

	/* ackreq default behaviour */
	if (nla_put_u8(msg, NL802154_ATTR_ACKREQ_DEFAULT, wpan_dev->ackreq))
		goto nla_put_failure;

#ifdef CONFIG_IEEE802154_NL802154_EXPERIMENTAL
	if (nl802154_get_llsec_params(msg, rdev, wpan_dev) < 0)
		goto nla_put_failure;
#endif /* CONFIG_IEEE802154_NL802154_EXPERIMENTAL */

	genlmsg_end(msg, hdr);
	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}