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
struct gsw_mt753x {int /*<<< orphan*/  (* mmd_write ) (struct gsw_mt753x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_DEV1E ; 
 int /*<<< orphan*/  PHY_DEV1E_REG_0FE ; 
 int /*<<< orphan*/  PHY_DEV1E_REG_41 ; 
 int /*<<< orphan*/  PHY_DEV1F ; 
 int /*<<< orphan*/  PHY_DEV1F_REG_268 ; 
 int /*<<< orphan*/  PHY_DEV1F_REG_269 ; 
 int /*<<< orphan*/  RXADC_CONTROL_3 ; 
 int /*<<< orphan*/  RXADC_LDO_CONTROL_2 ; 
 int /*<<< orphan*/  TXVLD_DA_271 ; 
 int /*<<< orphan*/  TXVLD_DA_272 ; 
 int /*<<< orphan*/  TXVLD_DA_273 ; 
 int /*<<< orphan*/  stub1 (struct gsw_mt753x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct gsw_mt753x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct gsw_mt753x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct gsw_mt753x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct gsw_mt753x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct gsw_mt753x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct gsw_mt753x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (struct gsw_mt753x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (struct gsw_mt753x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt7531_adjust_line_driving(struct gsw_mt753x *gsw, u32 port)
{
	/* For ADC timing margin window for LDO calibration */
	gsw->mmd_write(gsw, port, PHY_DEV1E, RXADC_LDO_CONTROL_2, 0x2222);

	/* Adjust AD sample timing */
	gsw->mmd_write(gsw, port, PHY_DEV1E, RXADC_CONTROL_3, 0x4444);

	/* Adjust Line driver current for different mode */
	gsw->mmd_write(gsw, port, PHY_DEV1F, TXVLD_DA_271, 0x2ca5);

	/* Adjust Line driver current for different mode */
	gsw->mmd_write(gsw, port, PHY_DEV1F, TXVLD_DA_272, 0xc6b);

	/* Adjust Line driver amplitude for 10BT */
	gsw->mmd_write(gsw, port, PHY_DEV1F, TXVLD_DA_273, 0x3000);

	/* Adjust RX Echo path filter */
	gsw->mmd_write(gsw, port, PHY_DEV1E, PHY_DEV1E_REG_0FE, 0x2);

	/* Adjust RX HVGA bias current */
	gsw->mmd_write(gsw, port, PHY_DEV1E, PHY_DEV1E_REG_41, 0x3333);

	/* Adjust TX class AB driver 1 */
	gsw->mmd_write(gsw, port, PHY_DEV1F, PHY_DEV1F_REG_268, 0x388);

	/* Adjust TX class AB driver 2 */
	gsw->mmd_write(gsw, port, PHY_DEV1F, PHY_DEV1F_REG_269, 0x4448);
}