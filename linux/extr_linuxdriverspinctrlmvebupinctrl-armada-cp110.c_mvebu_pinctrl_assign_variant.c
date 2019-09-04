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
typedef  int /*<<< orphan*/  u8 ;
struct mvebu_mpp_mode {struct mvebu_mpp_ctrl_setting* settings; } ;
struct mvebu_mpp_ctrl_setting {int /*<<< orphan*/  variant; scalar_t__ name; } ;

/* Variables and functions */

__attribute__((used)) static void mvebu_pinctrl_assign_variant(struct mvebu_mpp_mode *m,
					 u8 variant)
{
	struct mvebu_mpp_ctrl_setting *s;

	for (s = m->settings ; s->name ; s++)
		s->variant = variant;
}