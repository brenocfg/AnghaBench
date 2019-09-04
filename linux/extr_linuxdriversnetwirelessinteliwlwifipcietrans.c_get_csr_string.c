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

/* Variables and functions */
#define  CSR_ANA_PLL_CFG 151 
#define  CSR_DBG_HPET_MEM_REG 150 
#define  CSR_DRAM_INT_TBL_REG 149 
#define  CSR_EEPROM_GP 148 
#define  CSR_EEPROM_REG 147 
#define  CSR_FH_INT_STATUS 146 
#define  CSR_GIO_CHICKEN_BITS 145 
#define  CSR_GIO_REG 144 
#define  CSR_GPIO_IN 143 
#define  CSR_GP_CNTRL 142 
#define  CSR_GP_DRIVER_REG 141 
#define  CSR_GP_UCODE_REG 140 
#define  CSR_HW_IF_CONFIG_REG 139 
#define  CSR_HW_REV 138 
#define  CSR_HW_REV_WA_REG 137 
#define  CSR_INT 136 
#define  CSR_INT_COALESCING 135 
#define  CSR_INT_MASK 134 
#define  CSR_LED_REG 133 
#define  CSR_MONITOR_STATUS_REG 132 
#define  CSR_OTP_GP_REG 131 
#define  CSR_RESET 130 
#define  CSR_UCODE_DRV_GP1 129 
#define  CSR_UCODE_DRV_GP2 128 

__attribute__((used)) static const char *get_csr_string(int cmd)
{
#define IWL_CMD(x) case x: return #x
	switch (cmd) {
	IWL_CMD(CSR_HW_IF_CONFIG_REG);
	IWL_CMD(CSR_INT_COALESCING);
	IWL_CMD(CSR_INT);
	IWL_CMD(CSR_INT_MASK);
	IWL_CMD(CSR_FH_INT_STATUS);
	IWL_CMD(CSR_GPIO_IN);
	IWL_CMD(CSR_RESET);
	IWL_CMD(CSR_GP_CNTRL);
	IWL_CMD(CSR_HW_REV);
	IWL_CMD(CSR_EEPROM_REG);
	IWL_CMD(CSR_EEPROM_GP);
	IWL_CMD(CSR_OTP_GP_REG);
	IWL_CMD(CSR_GIO_REG);
	IWL_CMD(CSR_GP_UCODE_REG);
	IWL_CMD(CSR_GP_DRIVER_REG);
	IWL_CMD(CSR_UCODE_DRV_GP1);
	IWL_CMD(CSR_UCODE_DRV_GP2);
	IWL_CMD(CSR_LED_REG);
	IWL_CMD(CSR_DRAM_INT_TBL_REG);
	IWL_CMD(CSR_GIO_CHICKEN_BITS);
	IWL_CMD(CSR_ANA_PLL_CFG);
	IWL_CMD(CSR_HW_REV_WA_REG);
	IWL_CMD(CSR_MONITOR_STATUS_REG);
	IWL_CMD(CSR_DBG_HPET_MEM_REG);
	default:
		return "UNKNOWN";
	}
#undef IWL_CMD
}