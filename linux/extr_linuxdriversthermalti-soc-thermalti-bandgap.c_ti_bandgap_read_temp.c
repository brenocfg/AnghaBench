#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ti_bandgap {TYPE_2__* conf; } ;
struct temp_sensor_registers {int /*<<< orphan*/  bgap_dtemp_mask; int /*<<< orphan*/  ctrl_dtemp_1; int /*<<< orphan*/  temp_sensor_ctrl; } ;
struct TYPE_4__ {TYPE_1__* sensors; } ;
struct TYPE_3__ {struct temp_sensor_registers* registers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRATA_814 ; 
 int /*<<< orphan*/  FREEZE_BIT ; 
 int /*<<< orphan*/  RMW_BITS (struct ti_bandgap*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TI_BANDGAP_HAS (struct ti_bandgap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgap_mask_ctrl ; 
 int /*<<< orphan*/  mask_freeze_mask ; 
 int /*<<< orphan*/  ti_bandgap_readl (struct ti_bandgap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_errata814_bandgap_read_temp (struct ti_bandgap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ti_bandgap_read_temp(struct ti_bandgap *bgp, int id)
{
	struct temp_sensor_registers *tsr;
	u32 temp, reg;

	tsr = bgp->conf->sensors[id].registers;
	reg = tsr->temp_sensor_ctrl;

	if (TI_BANDGAP_HAS(bgp, FREEZE_BIT)) {
		RMW_BITS(bgp, id, bgap_mask_ctrl, mask_freeze_mask, 1);
		/*
		 * In case we cannot read from cur_dtemp / dtemp_0,
		 * then we read from the last valid temp read
		 */
		reg = tsr->ctrl_dtemp_1;
	}

	/* read temperature */
	if (TI_BANDGAP_HAS(bgp, ERRATA_814))
		temp = ti_errata814_bandgap_read_temp(bgp, reg);
	else
		temp = ti_bandgap_readl(bgp, reg);

	temp &= tsr->bgap_dtemp_mask;

	if (TI_BANDGAP_HAS(bgp, FREEZE_BIT))
		RMW_BITS(bgp, id, bgap_mask_ctrl, mask_freeze_mask, 0);

	return temp;
}