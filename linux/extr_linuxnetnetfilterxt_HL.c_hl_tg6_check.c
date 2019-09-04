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
struct xt_tgchk_param {struct ip6t_HL_info* targinfo; } ;
struct ip6t_HL_info {scalar_t__ mode; scalar_t__ hop_limit; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IP6T_HL_MAXMODE ; 
 scalar_t__ IP6T_HL_SET ; 

__attribute__((used)) static int hl_tg6_check(const struct xt_tgchk_param *par)
{
	const struct ip6t_HL_info *info = par->targinfo;

	if (info->mode > IP6T_HL_MAXMODE)
		return -EINVAL;
	if (info->mode != IP6T_HL_SET && info->hop_limit == 0)
		return -EINVAL;
	return 0;
}