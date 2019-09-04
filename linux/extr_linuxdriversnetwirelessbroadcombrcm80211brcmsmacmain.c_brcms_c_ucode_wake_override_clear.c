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
typedef  int /*<<< orphan*/  u32 ;
struct brcms_hardware {int maccontrol; scalar_t__ wake_override; } ;

/* Variables and functions */
 int MCTL_WAKE ; 
 int /*<<< orphan*/  brcms_c_mctrl_write (struct brcms_hardware*) ; 
 int /*<<< orphan*/  mboolclr (scalar_t__,int /*<<< orphan*/ ) ; 

void brcms_c_ucode_wake_override_clear(struct brcms_hardware *wlc_hw,
				   u32 override_bit)
{
	mboolclr(wlc_hw->wake_override, override_bit);

	if (wlc_hw->wake_override || (wlc_hw->maccontrol & MCTL_WAKE))
		return;

	brcms_c_mctrl_write(wlc_hw);
}