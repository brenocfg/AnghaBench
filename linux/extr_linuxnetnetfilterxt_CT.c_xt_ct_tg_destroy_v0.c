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
struct xt_tgdtor_param {struct xt_ct_target_info* targinfo; } ;
struct xt_ct_target_info_v1 {int /*<<< orphan*/  helper; int /*<<< orphan*/  ct; int /*<<< orphan*/  exp_events; int /*<<< orphan*/  ct_events; int /*<<< orphan*/  zone; int /*<<< orphan*/  flags; } ;
struct xt_ct_target_info {int /*<<< orphan*/  helper; int /*<<< orphan*/  ct; int /*<<< orphan*/  exp_events; int /*<<< orphan*/  ct_events; int /*<<< orphan*/  zone; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xt_ct_tg_destroy (struct xt_tgdtor_param const*,struct xt_ct_target_info_v1*) ; 

__attribute__((used)) static void xt_ct_tg_destroy_v0(const struct xt_tgdtor_param *par)
{
	struct xt_ct_target_info *info = par->targinfo;
	struct xt_ct_target_info_v1 info_v1 = {
		.flags 		= info->flags,
		.zone		= info->zone,
		.ct_events	= info->ct_events,
		.exp_events	= info->exp_events,
		.ct		= info->ct,
	};
	memcpy(info_v1.helper, info->helper, sizeof(info->helper));

	xt_ct_tg_destroy(par, &info_v1);
}