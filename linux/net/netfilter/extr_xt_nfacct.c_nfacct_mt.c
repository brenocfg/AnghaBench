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
struct xt_nfacct_match_info {int /*<<< orphan*/  nfacct; } ;
struct xt_action_param {struct xt_nfacct_match_info* targinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int NFACCT_UNDERQUOTA ; 
 int nfnl_acct_overquota (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnl_acct_update (struct sk_buff const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xt_net (struct xt_action_param*) ; 

__attribute__((used)) static bool nfacct_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	int overquota;
	const struct xt_nfacct_match_info *info = par->targinfo;

	nfnl_acct_update(skb, info->nfacct);

	overquota = nfnl_acct_overquota(xt_net(par), info->nfacct);

	return overquota == NFACCT_UNDERQUOTA ? false : true;
}