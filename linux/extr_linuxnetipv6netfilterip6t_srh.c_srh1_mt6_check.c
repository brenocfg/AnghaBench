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
struct xt_mtchk_param {struct ip6t_srh1* matchinfo; } ;
struct ip6t_srh1 {int mt_flags; int mt_invflags; } ;

/* Variables and functions */
 int EINVAL ; 
 int IP6T_SRH_INV_MASK ; 
 int IP6T_SRH_MASK ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int) ; 

__attribute__((used)) static int srh1_mt6_check(const struct xt_mtchk_param *par)
{
	const struct ip6t_srh1 *srhinfo = par->matchinfo;

	if (srhinfo->mt_flags & ~IP6T_SRH_MASK) {
		pr_info_ratelimited("unknown srh match flags  %X\n",
				    srhinfo->mt_flags);
		return -EINVAL;
	}

	if (srhinfo->mt_invflags & ~IP6T_SRH_INV_MASK) {
		pr_info_ratelimited("unknown srh invflags %X\n",
				    srhinfo->mt_invflags);
		return -EINVAL;
	}

	return 0;
}