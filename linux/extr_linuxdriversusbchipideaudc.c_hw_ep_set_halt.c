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
typedef  int u32 ;
struct ci_hdrc {int dummy; } ;
typedef  enum ci_hw_regs { ____Placeholder_ci_hw_regs } ci_hw_regs ;

/* Variables and functions */
 int EINVAL ; 
 int ENDPTCTRL_RXR ; 
 int ENDPTCTRL_RXS ; 
 int ENDPTCTRL_TXR ; 
 int ENDPTCTRL_TXS ; 
 int OP_ENDPTCTRL ; 
 int TX ; 
 int hw_ep_get_halt (struct ci_hdrc*,int,int) ; 
 int /*<<< orphan*/  hw_write (struct ci_hdrc*,int,int,int) ; 

__attribute__((used)) static int hw_ep_set_halt(struct ci_hdrc *ci, int num, int dir, int value)
{
	if (value != 0 && value != 1)
		return -EINVAL;

	do {
		enum ci_hw_regs reg = OP_ENDPTCTRL + num;
		u32 mask_xs = (dir == TX) ? ENDPTCTRL_TXS : ENDPTCTRL_RXS;
		u32 mask_xr = (dir == TX) ? ENDPTCTRL_TXR : ENDPTCTRL_RXR;

		/* data toggle - reserved for EP0 but it's in ESS */
		hw_write(ci, reg, mask_xs|mask_xr,
			  value ? mask_xs : mask_xr);
	} while (value != hw_ep_get_halt(ci, num, dir));

	return 0;
}