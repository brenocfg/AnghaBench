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
struct xt_tgchk_param {struct ipt_TTL_info* targinfo; } ;
struct ipt_TTL_info {scalar_t__ mode; scalar_t__ ttl; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IPT_TTL_MAXMODE ; 
 scalar_t__ IPT_TTL_SET ; 

__attribute__((used)) static int ttl_tg_check(const struct xt_tgchk_param *par)
{
	const struct ipt_TTL_info *info = par->targinfo;

	if (info->mode > IPT_TTL_MAXMODE)
		return -EINVAL;
	if (info->mode != IPT_TTL_SET && info->ttl == 0)
		return -EINVAL;
	return 0;
}