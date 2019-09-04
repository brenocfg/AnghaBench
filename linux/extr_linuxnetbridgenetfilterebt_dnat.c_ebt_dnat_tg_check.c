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
struct xt_tgchk_param {int hook_mask; int /*<<< orphan*/  table; struct ebt_nat_info* targinfo; } ;
struct ebt_nat_info {scalar_t__ target; } ;

/* Variables and functions */
 scalar_t__ BASE_CHAIN ; 
 scalar_t__ EBT_RETURN ; 
 int EINVAL ; 
 int NF_BR_BROUTING ; 
 int NF_BR_LOCAL_OUT ; 
 int NF_BR_NUMHOOKS ; 
 int NF_BR_PRE_ROUTING ; 
 scalar_t__ ebt_invalid_target (scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ebt_dnat_tg_check(const struct xt_tgchk_param *par)
{
	const struct ebt_nat_info *info = par->targinfo;
	unsigned int hook_mask;

	if (BASE_CHAIN && info->target == EBT_RETURN)
		return -EINVAL;

	hook_mask = par->hook_mask & ~(1 << NF_BR_NUMHOOKS);
	if ((strcmp(par->table, "nat") != 0 ||
	    (hook_mask & ~((1 << NF_BR_PRE_ROUTING) |
	    (1 << NF_BR_LOCAL_OUT)))) &&
	    (strcmp(par->table, "broute") != 0 ||
	    hook_mask & ~(1 << NF_BR_BROUTING)))
		return -EINVAL;
	if (ebt_invalid_target(info->target))
		return -EINVAL;
	return 0;
}