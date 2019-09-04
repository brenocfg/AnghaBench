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
struct xonar_pcm179x {int* cs2000_regs; } ;
struct oxygen {struct xonar_pcm179x* model_data; } ;

/* Variables and functions */
 int CS2000_AUX_OUT_SRC_REF_CLK ; 
 size_t CS2000_DEV_CFG_1 ; 
 size_t CS2000_DEV_CFG_2 ; 
 size_t CS2000_DEV_CTRL ; 
 int CS2000_EN_DEV_CFG_1 ; 
 int CS2000_EN_DEV_CFG_2 ; 
 int CS2000_FRAC_N_SRC_STATIC ; 
 int CS2000_FREEZE ; 
 size_t CS2000_FUN_CFG_1 ; 
 size_t CS2000_FUN_CFG_2 ; 
 size_t CS2000_GLOBAL_CFG ; 
 int CS2000_LOCK_CLK_SHIFT ; 
 int CS2000_RATIO_0 ; 
 int CS2000_R_MOD_SEL_1 ; 
 int CS2000_R_SEL_SHIFT ; 
 int /*<<< orphan*/  cs2000_write (struct oxygen*,size_t,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void cs2000_registers_init(struct oxygen *chip)
{
	struct xonar_pcm179x *data = chip->model_data;

	cs2000_write(chip, CS2000_GLOBAL_CFG, CS2000_FREEZE);
	cs2000_write(chip, CS2000_DEV_CTRL, 0);
	cs2000_write(chip, CS2000_DEV_CFG_1,
		     CS2000_R_MOD_SEL_1 |
		     (0 << CS2000_R_SEL_SHIFT) |
		     CS2000_AUX_OUT_SRC_REF_CLK |
		     CS2000_EN_DEV_CFG_1);
	cs2000_write(chip, CS2000_DEV_CFG_2,
		     (0 << CS2000_LOCK_CLK_SHIFT) |
		     CS2000_FRAC_N_SRC_STATIC);
	cs2000_write(chip, CS2000_RATIO_0 + 0, 0x00); /* 1.0 */
	cs2000_write(chip, CS2000_RATIO_0 + 1, 0x10);
	cs2000_write(chip, CS2000_RATIO_0 + 2, 0x00);
	cs2000_write(chip, CS2000_RATIO_0 + 3, 0x00);
	cs2000_write(chip, CS2000_FUN_CFG_1,
		     data->cs2000_regs[CS2000_FUN_CFG_1]);
	cs2000_write(chip, CS2000_FUN_CFG_2, 0);
	cs2000_write(chip, CS2000_GLOBAL_CFG, CS2000_EN_DEV_CFG_2);
	msleep(3); /* PLL lock delay */
}