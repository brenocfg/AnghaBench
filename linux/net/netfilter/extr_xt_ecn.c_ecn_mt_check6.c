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
struct xt_mtchk_param {struct ip6t_ip6* entryinfo; struct xt_ecn_info* matchinfo; } ;
struct xt_ecn_info {int operation; int invert; } ;
struct ip6t_ip6 {scalar_t__ proto; int invflags; } ;

/* Variables and functions */
 int EINVAL ; 
 int IP6T_INV_PROTO ; 
 scalar_t__ IPPROTO_TCP ; 
 int XT_ECN_OP_MATCH_CWR ; 
 int XT_ECN_OP_MATCH_ECE ; 
 int XT_ECN_OP_MATCH_MASK ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*) ; 

__attribute__((used)) static int ecn_mt_check6(const struct xt_mtchk_param *par)
{
	const struct xt_ecn_info *info = par->matchinfo;
	const struct ip6t_ip6 *ip = par->entryinfo;

	if (info->operation & XT_ECN_OP_MATCH_MASK)
		return -EINVAL;

	if (info->invert & XT_ECN_OP_MATCH_MASK)
		return -EINVAL;

	if (info->operation & (XT_ECN_OP_MATCH_ECE | XT_ECN_OP_MATCH_CWR) &&
	    (ip->proto != IPPROTO_TCP || ip->invflags & IP6T_INV_PROTO)) {
		pr_info_ratelimited("cannot match TCP bits for non-tcp packets\n");
		return -EINVAL;
	}

	return 0;
}