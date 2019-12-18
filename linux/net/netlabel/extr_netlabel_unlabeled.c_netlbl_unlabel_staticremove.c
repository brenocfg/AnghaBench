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
struct netlbl_audit {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NLBL_UNLABEL_A_IFACE ; 
 size_t NLBL_UNLABEL_A_IPV4ADDR ; 
 size_t NLBL_UNLABEL_A_IPV4MASK ; 
 size_t NLBL_UNLABEL_A_IPV6ADDR ; 
 size_t NLBL_UNLABEL_A_IPV6MASK ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  netlbl_netlink_auditinfo (struct sk_buff*,struct netlbl_audit*) ; 
 int netlbl_unlabel_addrinfo_get (struct genl_info*,void**,void**,int /*<<< orphan*/ *) ; 
 int netlbl_unlhsh_remove (int /*<<< orphan*/ *,char*,void*,void*,int /*<<< orphan*/ ,struct netlbl_audit*) ; 
 char* nla_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netlbl_unlabel_staticremove(struct sk_buff *skb,
				       struct genl_info *info)
{
	int ret_val;
	char *dev_name;
	void *addr;
	void *mask;
	u32 addr_len;
	struct netlbl_audit audit_info;

	/* See the note in netlbl_unlabel_staticadd() about not allowing both
	 * IPv4 and IPv6 in the same entry. */
	if (!info->attrs[NLBL_UNLABEL_A_IFACE] ||
	    !((!info->attrs[NLBL_UNLABEL_A_IPV4ADDR] ||
	       !info->attrs[NLBL_UNLABEL_A_IPV4MASK]) ^
	      (!info->attrs[NLBL_UNLABEL_A_IPV6ADDR] ||
	       !info->attrs[NLBL_UNLABEL_A_IPV6MASK])))
		return -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);

	ret_val = netlbl_unlabel_addrinfo_get(info, &addr, &mask, &addr_len);
	if (ret_val != 0)
		return ret_val;
	dev_name = nla_data(info->attrs[NLBL_UNLABEL_A_IFACE]);

	return netlbl_unlhsh_remove(&init_net,
				    dev_name, addr, mask, addr_len,
				    &audit_info);
}