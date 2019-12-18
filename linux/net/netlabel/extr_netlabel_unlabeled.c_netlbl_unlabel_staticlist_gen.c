#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct netlbl_unlhsh_walk_arg {int /*<<< orphan*/  skb; int /*<<< orphan*/  seq; TYPE_1__* nl_cb; } ;
struct netlbl_unlhsh_iface {scalar_t__ ifindex; } ;
struct TYPE_7__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct netlbl_unlhsh_addr6 {int /*<<< orphan*/  secid; TYPE_3__ list; } ;
struct TYPE_6__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct netlbl_unlhsh_addr4 {int /*<<< orphan*/  secid; TYPE_2__ list; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  portid; } ;
struct TYPE_5__ {int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 TYPE_4__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLBL_UNLABEL_A_IFACE ; 
 int /*<<< orphan*/  NLBL_UNLABEL_A_IPV4ADDR ; 
 int /*<<< orphan*/  NLBL_UNLABEL_A_IPV4MASK ; 
 int /*<<< orphan*/  NLBL_UNLABEL_A_IPV6ADDR ; 
 int /*<<< orphan*/  NLBL_UNLABEL_A_IPV6MASK ; 
 int /*<<< orphan*/  NLBL_UNLABEL_A_SECCTX ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  genlmsg_cancel (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  genlmsg_end (int /*<<< orphan*/ ,void*) ; 
 void* genlmsg_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  netlbl_unlabel_gnl_family ; 
 int nla_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int nla_put_in6_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nla_put_in_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nla_put_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_release_secctx (char*,int /*<<< orphan*/ ) ; 
 int security_secid_to_secctx (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netlbl_unlabel_staticlist_gen(u32 cmd,
				       const struct netlbl_unlhsh_iface *iface,
				       const struct netlbl_unlhsh_addr4 *addr4,
				       const struct netlbl_unlhsh_addr6 *addr6,
				       void *arg)
{
	int ret_val = -ENOMEM;
	struct netlbl_unlhsh_walk_arg *cb_arg = arg;
	struct net_device *dev;
	void *data;
	u32 secid;
	char *secctx;
	u32 secctx_len;

	data = genlmsg_put(cb_arg->skb, NETLINK_CB(cb_arg->nl_cb->skb).portid,
			   cb_arg->seq, &netlbl_unlabel_gnl_family,
			   NLM_F_MULTI, cmd);
	if (data == NULL)
		goto list_cb_failure;

	if (iface->ifindex > 0) {
		dev = dev_get_by_index(&init_net, iface->ifindex);
		if (!dev) {
			ret_val = -ENODEV;
			goto list_cb_failure;
		}
		ret_val = nla_put_string(cb_arg->skb,
					 NLBL_UNLABEL_A_IFACE, dev->name);
		dev_put(dev);
		if (ret_val != 0)
			goto list_cb_failure;
	}

	if (addr4) {
		struct in_addr addr_struct;

		addr_struct.s_addr = addr4->list.addr;
		ret_val = nla_put_in_addr(cb_arg->skb,
					  NLBL_UNLABEL_A_IPV4ADDR,
					  addr_struct.s_addr);
		if (ret_val != 0)
			goto list_cb_failure;

		addr_struct.s_addr = addr4->list.mask;
		ret_val = nla_put_in_addr(cb_arg->skb,
					  NLBL_UNLABEL_A_IPV4MASK,
					  addr_struct.s_addr);
		if (ret_val != 0)
			goto list_cb_failure;

		secid = addr4->secid;
	} else {
		ret_val = nla_put_in6_addr(cb_arg->skb,
					   NLBL_UNLABEL_A_IPV6ADDR,
					   &addr6->list.addr);
		if (ret_val != 0)
			goto list_cb_failure;

		ret_val = nla_put_in6_addr(cb_arg->skb,
					   NLBL_UNLABEL_A_IPV6MASK,
					   &addr6->list.mask);
		if (ret_val != 0)
			goto list_cb_failure;

		secid = addr6->secid;
	}

	ret_val = security_secid_to_secctx(secid, &secctx, &secctx_len);
	if (ret_val != 0)
		goto list_cb_failure;
	ret_val = nla_put(cb_arg->skb,
			  NLBL_UNLABEL_A_SECCTX,
			  secctx_len,
			  secctx);
	security_release_secctx(secctx, secctx_len);
	if (ret_val != 0)
		goto list_cb_failure;

	cb_arg->seq++;
	genlmsg_end(cb_arg->skb, data);
	return 0;

list_cb_failure:
	genlmsg_cancel(cb_arg->skb, data);
	return ret_val;
}