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
struct xt_mtchk_param {struct xt_ipcomp* matchinfo; } ;
struct xt_ipcomp {int invflags; } ;

/* Variables and functions */
 int EINVAL ; 
 int XT_IPCOMP_INV_MASK ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int) ; 

__attribute__((used)) static int comp_mt_check(const struct xt_mtchk_param *par)
{
	const struct xt_ipcomp *compinfo = par->matchinfo;

	/* Must specify no unknown invflags */
	if (compinfo->invflags & ~XT_IPCOMP_INV_MASK) {
		pr_info_ratelimited("unknown flags %X\n", compinfo->invflags);
		return -EINVAL;
	}
	return 0;
}