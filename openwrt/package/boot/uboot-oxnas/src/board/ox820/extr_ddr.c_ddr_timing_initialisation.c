#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_3__ {int holdoff_cmd_A; int holdoff_cmd_ARW; int holdoff_cmd_N; int holdoff_cmd_LM; int holdoff_cmd_R; int holdoff_cmd_W; int holdoff_cmd_PC; int holdoff_cmd_RF; int holdoff_bank_R; int holdoff_bank_W; int holdoff_dir_RW; int holdoff_dir_WR; int latency_CAS; int latency_WL; int holdoff_FAW; int width_update; int odt_offset; int odt_drive_all; int use_fixed_re; int delay_wr_to_re; int wr_slave_ratio; int rd_slave_ratio0; int rd_slave_ratio1; } ;
typedef  TYPE_1__ T_DDR_TIMING_PARAMETERS ;

/* Variables and functions */
 scalar_t__ C_DDR_REG_PHY_RD_RATIO ; 
 scalar_t__ C_DDR_REG_PHY_TIMING ; 
 scalar_t__ C_DDR_REG_PHY_WR_RATIO ; 
 scalar_t__ C_DDR_REG_TIMING0 ; 
 scalar_t__ C_DDR_REG_TIMING1 ; 
 scalar_t__ C_DDR_REG_TIMING2 ; 

__attribute__((used)) static void ddr_timing_initialisation(
	const T_DDR_TIMING_PARAMETERS *ddr_timing_parameters)
{
	volatile UINT reg_tmp = 0;
	/* update the DDR controller registers for timing parameters */
	reg_tmp = (ddr_timing_parameters->holdoff_cmd_A << 0);
	reg_tmp = reg_tmp + (ddr_timing_parameters->holdoff_cmd_ARW << 4);
	reg_tmp = reg_tmp + (ddr_timing_parameters->holdoff_cmd_N << 8);
	reg_tmp = reg_tmp + (ddr_timing_parameters->holdoff_cmd_LM << 12);
	reg_tmp = reg_tmp + (ddr_timing_parameters->holdoff_cmd_R << 16);
	reg_tmp = reg_tmp + (ddr_timing_parameters->holdoff_cmd_W << 20);
	reg_tmp = reg_tmp + (ddr_timing_parameters->holdoff_cmd_PC << 24);
	*(volatile UINT *) C_DDR_REG_TIMING0 = reg_tmp;

	reg_tmp = (ddr_timing_parameters->holdoff_cmd_RF << 0);
	reg_tmp = reg_tmp + (ddr_timing_parameters->holdoff_bank_R << 8);
	reg_tmp = reg_tmp + (ddr_timing_parameters->holdoff_bank_W << 16);
	reg_tmp = reg_tmp + (ddr_timing_parameters->holdoff_dir_RW << 24);
	reg_tmp = reg_tmp + (ddr_timing_parameters->holdoff_dir_WR << 28);
	*(volatile UINT *) C_DDR_REG_TIMING1 = reg_tmp;

	reg_tmp = (ddr_timing_parameters->latency_CAS << 0);
	reg_tmp = reg_tmp + (ddr_timing_parameters->latency_WL << 4);
	reg_tmp = reg_tmp + (ddr_timing_parameters->holdoff_FAW << 8);
	reg_tmp = reg_tmp + (ddr_timing_parameters->width_update << 16);
	reg_tmp = reg_tmp + (ddr_timing_parameters->odt_offset << 21);
	reg_tmp = reg_tmp + (ddr_timing_parameters->odt_drive_all << 24);

	*(volatile UINT *) C_DDR_REG_TIMING2 = reg_tmp;

	/* Program the timing parameters in the PHY too */
	reg_tmp = (ddr_timing_parameters->use_fixed_re << 16)
			| (ddr_timing_parameters->delay_wr_to_re << 8)
			| (ddr_timing_parameters->latency_WL << 4)
			| (ddr_timing_parameters->latency_CAS << 0);

	*(volatile UINT *) C_DDR_REG_PHY_TIMING = reg_tmp;

	reg_tmp = ddr_timing_parameters->wr_slave_ratio;

	*(volatile UINT *) C_DDR_REG_PHY_WR_RATIO = reg_tmp;

	reg_tmp = ddr_timing_parameters->rd_slave_ratio0;
	reg_tmp += ddr_timing_parameters->rd_slave_ratio1 << 8;

	*(volatile UINT *) C_DDR_REG_PHY_RD_RATIO = reg_tmp;

}