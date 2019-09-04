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
struct xt_mtchk_param {int hook_mask; struct xt_devgroup_info* matchinfo; } ;
struct xt_devgroup_info {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int NF_INET_FORWARD ; 
 int NF_INET_LOCAL_IN ; 
 int NF_INET_LOCAL_OUT ; 
 int NF_INET_POST_ROUTING ; 
 int NF_INET_PRE_ROUTING ; 
 int XT_DEVGROUP_INVERT_DST ; 
 int XT_DEVGROUP_INVERT_SRC ; 
 int XT_DEVGROUP_MATCH_DST ; 
 int XT_DEVGROUP_MATCH_SRC ; 

__attribute__((used)) static int devgroup_mt_checkentry(const struct xt_mtchk_param *par)
{
	const struct xt_devgroup_info *info = par->matchinfo;

	if (info->flags & ~(XT_DEVGROUP_MATCH_SRC | XT_DEVGROUP_INVERT_SRC |
			    XT_DEVGROUP_MATCH_DST | XT_DEVGROUP_INVERT_DST))
		return -EINVAL;

	if (info->flags & XT_DEVGROUP_MATCH_SRC &&
	    par->hook_mask & ~((1 << NF_INET_PRE_ROUTING) |
			       (1 << NF_INET_LOCAL_IN) |
			       (1 << NF_INET_FORWARD)))
		return -EINVAL;

	if (info->flags & XT_DEVGROUP_MATCH_DST &&
	    par->hook_mask & ~((1 << NF_INET_FORWARD) |
			       (1 << NF_INET_LOCAL_OUT) |
			       (1 << NF_INET_POST_ROUTING)))
		return -EINVAL;

	return 0;
}