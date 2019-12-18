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
struct xt_mtchk_param {int /*<<< orphan*/  net; int /*<<< orphan*/  family; struct xt_connbytes_info* matchinfo; } ;
struct xt_connbytes_info {scalar_t__ what; scalar_t__ direction; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ XT_CONNBYTES_AVGPKT ; 
 scalar_t__ XT_CONNBYTES_BYTES ; 
 scalar_t__ XT_CONNBYTES_DIR_BOTH ; 
 scalar_t__ XT_CONNBYTES_DIR_ORIGINAL ; 
 scalar_t__ XT_CONNBYTES_DIR_REPLY ; 
 scalar_t__ XT_CONNBYTES_PKTS ; 
 int /*<<< orphan*/  nf_ct_acct_enabled (int /*<<< orphan*/ ) ; 
 int nf_ct_netns_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_set_acct (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int connbytes_mt_check(const struct xt_mtchk_param *par)
{
	const struct xt_connbytes_info *sinfo = par->matchinfo;
	int ret;

	if (sinfo->what != XT_CONNBYTES_PKTS &&
	    sinfo->what != XT_CONNBYTES_BYTES &&
	    sinfo->what != XT_CONNBYTES_AVGPKT)
		return -EINVAL;

	if (sinfo->direction != XT_CONNBYTES_DIR_ORIGINAL &&
	    sinfo->direction != XT_CONNBYTES_DIR_REPLY &&
	    sinfo->direction != XT_CONNBYTES_DIR_BOTH)
		return -EINVAL;

	ret = nf_ct_netns_get(par->net, par->family);
	if (ret < 0)
		pr_info_ratelimited("cannot load conntrack support for proto=%u\n",
				    par->family);

	/*
	 * This filter cannot function correctly unless connection tracking
	 * accounting is enabled, so complain in the hope that someone notices.
	 */
	if (!nf_ct_acct_enabled(par->net)) {
		pr_warn("Forcing CT accounting to be enabled\n");
		nf_ct_set_acct(par->net, true);
	}

	return ret;
}