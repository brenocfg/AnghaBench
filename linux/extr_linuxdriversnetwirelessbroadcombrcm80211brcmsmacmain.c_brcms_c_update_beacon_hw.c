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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct brcms_hardware {struct bcma_device* d11core; } ;
struct brcms_c_info {int beacon_template_virgin; int /*<<< orphan*/  defmacintmask; struct brcms_hardware* hw; } ;
struct bcma_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int MCMD_BCN0VLD ; 
 int MCMD_BCN1VLD ; 
 int /*<<< orphan*/  MI_BCNTPL ; 
 int bcma_read32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_set32 (struct bcma_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcma_write32 (struct bcma_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_beacon_write (struct brcms_c_info*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  maccommand ; 
 int /*<<< orphan*/  macintstatus ; 

__attribute__((used)) static void brcms_c_update_beacon_hw(struct brcms_c_info *wlc,
				     struct sk_buff *beacon, u16 tim_offset,
				     u16 dtim_period)
{
	struct brcms_hardware *wlc_hw = wlc->hw;
	struct bcma_device *core = wlc_hw->d11core;

	/* Hardware beaconing for this config */
	u32 both_valid = MCMD_BCN0VLD | MCMD_BCN1VLD;

	/* Check if both templates are in use, if so sched. an interrupt
	 *      that will call back into this routine
	 */
	if ((bcma_read32(core, D11REGOFFS(maccommand)) & both_valid) == both_valid)
		/* clear any previous status */
		bcma_write32(core, D11REGOFFS(macintstatus), MI_BCNTPL);

	if (wlc->beacon_template_virgin) {
		wlc->beacon_template_virgin = false;
		brcms_c_beacon_write(wlc, beacon, tim_offset, dtim_period, true,
				     true);
		/* mark beacon0 valid */
		bcma_set32(core, D11REGOFFS(maccommand), MCMD_BCN0VLD);
		return;
	}

	/* Check that after scheduling the interrupt both of the
	 *      templates are still busy. if not clear the int. & remask
	 */
	if ((bcma_read32(core, D11REGOFFS(maccommand)) & both_valid) == both_valid) {
		wlc->defmacintmask |= MI_BCNTPL;
		return;
	}

	if (!(bcma_read32(core, D11REGOFFS(maccommand)) & MCMD_BCN0VLD)) {
		brcms_c_beacon_write(wlc, beacon, tim_offset, dtim_period, true,
				     false);
		/* mark beacon0 valid */
		bcma_set32(core, D11REGOFFS(maccommand), MCMD_BCN0VLD);
		return;
	}
	if (!(bcma_read32(core, D11REGOFFS(maccommand)) & MCMD_BCN1VLD)) {
		brcms_c_beacon_write(wlc, beacon, tim_offset, dtim_period,
				     false, true);
		/* mark beacon0 valid */
		bcma_set32(core, D11REGOFFS(maccommand), MCMD_BCN1VLD);
		return;
	}
	return;
}