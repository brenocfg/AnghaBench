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
struct sk_buff {int dummy; } ;
struct netlbl_audit {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int EINVAL ; 
 size_t NLBL_MGMT_A_DOMAIN ; 
 int netlbl_domhsh_remove (char*,int /*<<< orphan*/ ,struct netlbl_audit*) ; 
 int /*<<< orphan*/  netlbl_netlink_auditinfo (struct sk_buff*,struct netlbl_audit*) ; 
 char* nla_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netlbl_mgmt_remove(struct sk_buff *skb, struct genl_info *info)
{
	char *domain;
	struct netlbl_audit audit_info;

	if (!info->attrs[NLBL_MGMT_A_DOMAIN])
		return -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);

	domain = nla_data(info->attrs[NLBL_MGMT_A_DOMAIN]);
	return netlbl_domhsh_remove(domain, AF_UNSPEC, &audit_info);
}