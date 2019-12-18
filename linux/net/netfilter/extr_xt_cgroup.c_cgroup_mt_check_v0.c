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
struct xt_mtchk_param {struct xt_cgroup_info_v0* matchinfo; } ;
struct xt_cgroup_info_v0 {int invert; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int cgroup_mt_check_v0(const struct xt_mtchk_param *par)
{
	struct xt_cgroup_info_v0 *info = par->matchinfo;

	if (info->invert & ~1)
		return -EINVAL;

	return 0;
}