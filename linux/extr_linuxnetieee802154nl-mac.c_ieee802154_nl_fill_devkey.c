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
struct ieee802154_llsec_device_key {int /*<<< orphan*/  key_id; int /*<<< orphan*/  frame_counter; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IEEE802154_ATTR_DEV_INDEX ; 
 int /*<<< orphan*/  IEEE802154_ATTR_DEV_NAME ; 
 int /*<<< orphan*/  IEEE802154_ATTR_HW_ADDR ; 
 int /*<<< orphan*/  IEEE802154_ATTR_LLSEC_FRAME_COUNTER ; 
 int /*<<< orphan*/  IEEE802154_ATTR_PAD ; 
 int /*<<< orphan*/  IEEE802154_LLSEC_LIST_DEVKEY ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee802154_llsec_fill_key_id (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl802154_family ; 
 scalar_t__ nla_put_hwaddr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ieee802154_nl_fill_devkey(struct sk_buff *msg, u32 portid, u32 seq,
			  __le64 devaddr,
			  const struct ieee802154_llsec_device_key *devkey,
			  const struct net_device *dev)
{
	void *hdr;

	hdr = genlmsg_put(msg, 0, seq, &nl802154_family, NLM_F_MULTI,
			  IEEE802154_LLSEC_LIST_DEVKEY);
	if (!hdr)
		goto out;

	if (nla_put_string(msg, IEEE802154_ATTR_DEV_NAME, dev->name) ||
	    nla_put_u32(msg, IEEE802154_ATTR_DEV_INDEX, dev->ifindex) ||
	    nla_put_hwaddr(msg, IEEE802154_ATTR_HW_ADDR, devaddr,
			   IEEE802154_ATTR_PAD) ||
	    nla_put_u32(msg, IEEE802154_ATTR_LLSEC_FRAME_COUNTER,
			devkey->frame_counter) ||
	    ieee802154_llsec_fill_key_id(msg, &devkey->key_id))
		goto nla_put_failure;

	genlmsg_end(msg, hdr);
	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
out:
	return -EMSGSIZE;
}