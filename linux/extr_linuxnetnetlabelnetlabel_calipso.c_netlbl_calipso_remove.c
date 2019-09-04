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
struct netlbl_domhsh_walk_arg {int /*<<< orphan*/  doi; struct netlbl_audit* audit_info; } ;
struct netlbl_audit {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 size_t NLBL_CALIPSO_A_DOI ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int calipso_doi_remove (int /*<<< orphan*/ ,struct netlbl_audit*) ; 
 int /*<<< orphan*/  netlabel_mgmt_protocount ; 
 int /*<<< orphan*/  netlbl_calipso_remove_cb ; 
 int netlbl_domhsh_walk (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct netlbl_domhsh_walk_arg*) ; 
 int /*<<< orphan*/  netlbl_netlink_auditinfo (struct sk_buff*,struct netlbl_audit*) ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netlbl_calipso_remove(struct sk_buff *skb, struct genl_info *info)
{
	int ret_val = -EINVAL;
	struct netlbl_domhsh_walk_arg cb_arg;
	struct netlbl_audit audit_info;
	u32 skip_bkt = 0;
	u32 skip_chain = 0;

	if (!info->attrs[NLBL_CALIPSO_A_DOI])
		return -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);
	cb_arg.doi = nla_get_u32(info->attrs[NLBL_CALIPSO_A_DOI]);
	cb_arg.audit_info = &audit_info;
	ret_val = netlbl_domhsh_walk(&skip_bkt, &skip_chain,
				     netlbl_calipso_remove_cb, &cb_arg);
	if (ret_val == 0 || ret_val == -ENOENT) {
		ret_val = calipso_doi_remove(cb_arg.doi, &audit_info);
		if (ret_val == 0)
			atomic_dec(&netlabel_mgmt_protocount);
	}

	return ret_val;
}