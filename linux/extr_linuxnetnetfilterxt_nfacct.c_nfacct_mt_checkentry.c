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
struct xt_nfacct_match_info {struct nf_acct* nfacct; int /*<<< orphan*/  name; } ;
struct xt_mtchk_param {int /*<<< orphan*/  net; struct xt_nfacct_match_info* matchinfo; } ;
struct nf_acct {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct nf_acct* nfnl_acct_find_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfacct_mt_checkentry(const struct xt_mtchk_param *par)
{
	struct xt_nfacct_match_info *info = par->matchinfo;
	struct nf_acct *nfacct;

	nfacct = nfnl_acct_find_get(par->net, info->name);
	if (nfacct == NULL) {
		pr_info_ratelimited("accounting object `%s' does not exists\n",
				    info->name);
		return -ENOENT;
	}
	info->nfacct = nfacct;
	return 0;
}