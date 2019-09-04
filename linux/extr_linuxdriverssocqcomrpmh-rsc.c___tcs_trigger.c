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
struct rsc_drv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSC_DRV_CONTROL ; 
 int /*<<< orphan*/  TCS_AMC_MODE_ENABLE ; 
 int /*<<< orphan*/  TCS_AMC_MODE_TRIGGER ; 
 int /*<<< orphan*/  read_tcs_reg (struct rsc_drv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_tcs_reg_sync (struct rsc_drv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __tcs_trigger(struct rsc_drv *drv, int tcs_id)
{
	u32 enable;

	/*
	 * HW req: Clear the DRV_CONTROL and enable TCS again
	 * While clearing ensure that the AMC mode trigger is cleared
	 * and then the mode enable is cleared.
	 */
	enable = read_tcs_reg(drv, RSC_DRV_CONTROL, tcs_id, 0);
	enable &= ~TCS_AMC_MODE_TRIGGER;
	write_tcs_reg_sync(drv, RSC_DRV_CONTROL, tcs_id, enable);
	enable &= ~TCS_AMC_MODE_ENABLE;
	write_tcs_reg_sync(drv, RSC_DRV_CONTROL, tcs_id, enable);

	/* Enable the AMC mode on the TCS and then trigger the TCS */
	enable = TCS_AMC_MODE_ENABLE;
	write_tcs_reg_sync(drv, RSC_DRV_CONTROL, tcs_id, enable);
	enable |= TCS_AMC_MODE_TRIGGER;
	write_tcs_reg_sync(drv, RSC_DRV_CONTROL, tcs_id, enable);
}