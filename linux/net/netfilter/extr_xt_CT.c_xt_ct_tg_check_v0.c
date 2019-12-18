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
struct xt_tgchk_param {struct xt_ct_target_info* targinfo; } ;
struct xt_ct_target_info_v1 {int flags; int /*<<< orphan*/  ct; int /*<<< orphan*/  helper; int /*<<< orphan*/  exp_events; int /*<<< orphan*/  ct_events; int /*<<< orphan*/  zone; } ;
struct xt_ct_target_info {int flags; int /*<<< orphan*/  ct; int /*<<< orphan*/  helper; int /*<<< orphan*/  exp_events; int /*<<< orphan*/  ct_events; int /*<<< orphan*/  zone; } ;

/* Variables and functions */
 int EINVAL ; 
 int XT_CT_NOTRACK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int xt_ct_tg_check (struct xt_tgchk_param const*,struct xt_ct_target_info_v1*) ; 

__attribute__((used)) static int xt_ct_tg_check_v0(const struct xt_tgchk_param *par)
{
	struct xt_ct_target_info *info = par->targinfo;
	struct xt_ct_target_info_v1 info_v1 = {
		.flags 		= info->flags,
		.zone		= info->zone,
		.ct_events	= info->ct_events,
		.exp_events	= info->exp_events,
	};
	int ret;

	if (info->flags & ~XT_CT_NOTRACK)
		return -EINVAL;

	memcpy(info_v1.helper, info->helper, sizeof(info->helper));

	ret = xt_ct_tg_check(par, &info_v1);
	if (ret < 0)
		return ret;

	info->ct = info_v1.ct;

	return ret;
}