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
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t SMC_PNETID_NAME ; 
 scalar_t__ nla_data (int /*<<< orphan*/ ) ; 
 int smc_pnet_remove_by_pnetid (char*) ; 

__attribute__((used)) static int smc_pnet_del(struct sk_buff *skb, struct genl_info *info)
{
	if (!info->attrs[SMC_PNETID_NAME])
		return -EINVAL;
	return smc_pnet_remove_by_pnetid(
				(char *)nla_data(info->attrs[SMC_PNETID_NAME]));
}