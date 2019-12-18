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
struct xt_mtchk_param {struct ip6t_mh* matchinfo; } ;
struct ip6t_mh {int invflags; } ;

/* Variables and functions */
 int EINVAL ; 
 int IP6T_MH_INV_MASK ; 

__attribute__((used)) static int mh_mt6_check(const struct xt_mtchk_param *par)
{
	const struct ip6t_mh *mhinfo = par->matchinfo;

	/* Must specify no unknown invflags */
	return (mhinfo->invflags & ~IP6T_MH_INV_MASK) ? -EINVAL : 0;
}