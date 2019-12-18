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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wireless_dev {int /*<<< orphan*/  conn_owner_nlportid; int /*<<< orphan*/  wiphy; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  protocol; } ;
struct nlattr {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; struct wireless_dev* ieee80211_ptr; } ;
struct ethhdr {int /*<<< orphan*/ * h_source; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; int /*<<< orphan*/  wiphy_idx; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NL80211_ATTR_CONTROL_PORT_ETHERTYPE ; 
 int /*<<< orphan*/  NL80211_ATTR_CONTROL_PORT_NO_ENCRYPT ; 
 int /*<<< orphan*/  NL80211_ATTR_FRAME ; 
 int /*<<< orphan*/  NL80211_ATTR_IFINDEX ; 
 int /*<<< orphan*/  NL80211_ATTR_MAC ; 
 int /*<<< orphan*/  NL80211_ATTR_PAD ; 
 int /*<<< orphan*/  NL80211_ATTR_WDEV ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  NL80211_CMD_CONTROL_PORT_FRAME ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int genlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdev_id (struct wireless_dev*) ; 
 int /*<<< orphan*/  wiphy_net (int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __nl80211_rx_control_port(struct net_device *dev,
				     struct sk_buff *skb,
				     bool unencrypted, gfp_t gfp)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	struct ethhdr *ehdr = eth_hdr(skb);
	const u8 *addr = ehdr->h_source;
	u16 proto = be16_to_cpu(skb->protocol);
	struct sk_buff *msg;
	void *hdr;
	struct nlattr *frame;

	u32 nlportid = READ_ONCE(wdev->conn_owner_nlportid);

	if (!nlportid)
		return -ENOENT;

	msg = nlmsg_new(100 + skb->len, gfp);
	if (!msg)
		return -ENOMEM;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_CONTROL_PORT_FRAME);
	if (!hdr) {
		nlmsg_free(msg);
		return -ENOBUFS;
	}

	if (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->ifindex) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, addr) ||
	    nla_put_u16(msg, NL80211_ATTR_CONTROL_PORT_ETHERTYPE, proto) ||
	    (unencrypted && nla_put_flag(msg,
					 NL80211_ATTR_CONTROL_PORT_NO_ENCRYPT)))
		goto nla_put_failure;

	frame = nla_reserve(msg, NL80211_ATTR_FRAME, skb->len);
	if (!frame)
		goto nla_put_failure;

	skb_copy_bits(skb, 0, nla_data(frame), skb->len);
	genlmsg_end(msg, hdr);

	return genlmsg_unicast(wiphy_net(&rdev->wiphy), msg, nlportid);

 nla_put_failure:
	nlmsg_free(msg);
	return -ENOBUFS;
}