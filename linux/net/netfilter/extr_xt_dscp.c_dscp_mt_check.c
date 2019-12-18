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
struct xt_mtchk_param {struct xt_dscp_info* matchinfo; } ;
struct xt_dscp_info {scalar_t__ dscp; } ;

/* Variables and functions */
 int EDOM ; 
 scalar_t__ XT_DSCP_MAX ; 

__attribute__((used)) static int dscp_mt_check(const struct xt_mtchk_param *par)
{
	const struct xt_dscp_info *info = par->matchinfo;

	if (info->dscp > XT_DSCP_MAX)
		return -EDOM;

	return 0;
}