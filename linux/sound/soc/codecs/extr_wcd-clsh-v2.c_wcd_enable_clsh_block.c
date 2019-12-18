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
struct wcd_clsh_ctrl {int clsh_users; struct snd_soc_component* comp; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCD9XXX_A_CDC_CLSH_CRC ; 
 int /*<<< orphan*/  WCD9XXX_A_CDC_CLSH_CRC_CLK_EN_MASK ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void wcd_enable_clsh_block(struct wcd_clsh_ctrl *ctrl,
					 bool enable)
{
	struct snd_soc_component *comp = ctrl->comp;

	if ((enable && ++ctrl->clsh_users == 1) ||
	    (!enable && --ctrl->clsh_users == 0))
		snd_soc_component_update_bits(comp, WCD9XXX_A_CDC_CLSH_CRC,
				      WCD9XXX_A_CDC_CLSH_CRC_CLK_EN_MASK,
				      enable);
	if (ctrl->clsh_users < 0)
		ctrl->clsh_users = 0;
}