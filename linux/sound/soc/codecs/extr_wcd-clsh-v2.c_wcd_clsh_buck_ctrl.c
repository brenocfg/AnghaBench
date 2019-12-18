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
struct wcd_clsh_ctrl {int buck_users; struct snd_soc_component* comp; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCD9XXX_A_ANA_RX_SUPPLIES ; 
 int /*<<< orphan*/  WCD9XXX_A_ANA_RX_VPOS_EN_MASK ; 
 int WCD9XXX_A_ANA_RX_VPOS_EN_SHIFT ; 
 scalar_t__ WCD_USLEEP_RANGE ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,scalar_t__) ; 

__attribute__((used)) static void wcd_clsh_buck_ctrl(struct wcd_clsh_ctrl *ctrl,
			       int mode,
			       bool enable)
{
	struct snd_soc_component *comp = ctrl->comp;

	/* enable/disable buck */
	if ((enable && (++ctrl->buck_users == 1)) ||
	   (!enable && (--ctrl->buck_users == 0)))
		snd_soc_component_update_bits(comp, WCD9XXX_A_ANA_RX_SUPPLIES,
				WCD9XXX_A_ANA_RX_VPOS_EN_MASK,
				enable << WCD9XXX_A_ANA_RX_VPOS_EN_SHIFT);
	/*
	 * 500us sleep is required after buck enable/disable
	 * as per HW requirement
	 */
	usleep_range(500, 500 + WCD_USLEEP_RANGE);
}