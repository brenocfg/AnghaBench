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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct batadv_priv {int /*<<< orphan*/  soft_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ATTR_ORIG_ADDRESS ; 
 int /*<<< orphan*/  BATADV_ATTR_PAD ; 
 int /*<<< orphan*/  BATADV_ATTR_TPMETER_BYTES ; 
 int /*<<< orphan*/  BATADV_ATTR_TPMETER_COOKIE ; 
 int /*<<< orphan*/  BATADV_ATTR_TPMETER_RESULT ; 
 int /*<<< orphan*/  BATADV_ATTR_TPMETER_TEST_TIME ; 
 int /*<<< orphan*/  BATADV_CMD_TP_METER ; 
 int /*<<< orphan*/  BATADV_NL_MCGRP_TPMETER ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  batadv_netlink_family ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_multicast_netns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int batadv_netlink_tpmeter_notify(struct batadv_priv *bat_priv, const u8 *dst,
				  u8 result, u32 test_time, u64 total_bytes,
				  u32 cookie)
{
	struct sk_buff *msg;
	void *hdr;
	int ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &batadv_netlink_family, 0,
			  BATADV_CMD_TP_METER);
	if (!hdr) {
		ret = -ENOBUFS;
		goto err_genlmsg;
	}

	if (nla_put_u32(msg, BATADV_ATTR_TPMETER_COOKIE, cookie))
		goto nla_put_failure;

	if (nla_put_u32(msg, BATADV_ATTR_TPMETER_TEST_TIME, test_time))
		goto nla_put_failure;

	if (nla_put_u64_64bit(msg, BATADV_ATTR_TPMETER_BYTES, total_bytes,
			      BATADV_ATTR_PAD))
		goto nla_put_failure;

	if (nla_put_u8(msg, BATADV_ATTR_TPMETER_RESULT, result))
		goto nla_put_failure;

	if (nla_put(msg, BATADV_ATTR_ORIG_ADDRESS, ETH_ALEN, dst))
		goto nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&batadv_netlink_family,
				dev_net(bat_priv->soft_iface), msg, 0,
				BATADV_NL_MCGRP_TPMETER, GFP_KERNEL);

	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	ret = -EMSGSIZE;

err_genlmsg:
	nlmsg_free(msg);
	return ret;
}