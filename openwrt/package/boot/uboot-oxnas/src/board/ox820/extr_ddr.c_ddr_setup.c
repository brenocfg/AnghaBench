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
typedef  int UINT ;
typedef  int /*<<< orphan*/  T_DDR_TIMING_PARAMETERS ;
typedef  int /*<<< orphan*/  T_DDR_CONFIG_PARAMETERS ;

/* Variables and functions */
 int C_BLKEN_DDR_ON ; 
 int /*<<< orphan*/  C_CP_DDR2_25_CL6 ; 
 scalar_t__ C_DDR_BLKEN_REG ; 
 scalar_t__ C_DDR_TRANSACTION_ROUTING ; 
 int /*<<< orphan*/  C_TP_DDR2_25_CL6_1GB ; 
 int DDR_ROUTE_CPU0_INSTR_SHIFT ; 
 int DDR_ROUTE_CPU0_RDDATA_SHIFT ; 
 int DDR_ROUTE_CPU0_WRDATA_SHIFT ; 
 int DDR_ROUTE_CPU1_INSTR_SHIFT ; 
 int DDR_ROUTE_CPU1_RDDATA_SHIFT ; 
 int DDR_ROUTE_CPU1_WRDATA_SHIFT ; 
 int /*<<< orphan*/  ddr_normal_initialisation (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ddr_timing_initialisation (int /*<<< orphan*/  const*) ; 

void ddr_setup(int mhz)
{
	static const T_DDR_TIMING_PARAMETERS *ddr_timing_parameters =
		&C_TP_DDR2_25_CL6_1GB;
	static const T_DDR_CONFIG_PARAMETERS *ddr_config_parameters =
		&C_CP_DDR2_25_CL6;

	//Bring core out of Reset
	*(volatile UINT *) C_DDR_BLKEN_REG = C_BLKEN_DDR_ON;

	//DDR TIMING INITIALISTION
	ddr_timing_initialisation(ddr_timing_parameters);

	//DDR NORMAL INITIALISATION
	ddr_normal_initialisation(ddr_config_parameters, mhz);

	// route all writes through one client
	*(volatile UINT *) C_DDR_TRANSACTION_ROUTING = (0
		<< DDR_ROUTE_CPU0_INSTR_SHIFT)
		| (1 << DDR_ROUTE_CPU0_RDDATA_SHIFT)
		| (3 << DDR_ROUTE_CPU0_WRDATA_SHIFT)
		| (2 << DDR_ROUTE_CPU1_INSTR_SHIFT)
		| (3 << DDR_ROUTE_CPU1_RDDATA_SHIFT)
		| (3 << DDR_ROUTE_CPU1_WRDATA_SHIFT);

	//Bring all clients out of reset
	*(volatile UINT *) C_DDR_BLKEN_REG = C_BLKEN_DDR_ON + 0x0000FFFF;

}