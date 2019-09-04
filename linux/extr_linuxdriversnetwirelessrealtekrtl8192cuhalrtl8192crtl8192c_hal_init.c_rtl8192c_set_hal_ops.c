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
struct hal_ops {int /*<<< orphan*/  c2h_id_filter_ccx; int /*<<< orphan*/  c2h_handler; int /*<<< orphan*/  hal_reset_security_engine; int /*<<< orphan*/ * hal_notch_filter; int /*<<< orphan*/ * Efuse_WordEnableDataWrite; int /*<<< orphan*/ * Efuse_PgPacketWrite; int /*<<< orphan*/ * Efuse_PgPacketRead; int /*<<< orphan*/ * EfuseGetCurrentSize; int /*<<< orphan*/ * EFUSEGetEfuseDefinition; int /*<<< orphan*/ * ReadEFuse; int /*<<< orphan*/ * EfusePowerSwitch; int /*<<< orphan*/ * write_rfreg; int /*<<< orphan*/ * read_rfreg; int /*<<< orphan*/ * write_bbreg; int /*<<< orphan*/ * read_bbreg; int /*<<< orphan*/ * Add_RateATid; int /*<<< orphan*/ * hal_dm_watchdog; int /*<<< orphan*/ * set_channel_handler; int /*<<< orphan*/ * set_bwmode_handler; int /*<<< orphan*/ * read_chip_version; int /*<<< orphan*/ * dm_deinit; int /*<<< orphan*/ * dm_init; int /*<<< orphan*/ * free_hal_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_SetBWMode8192C ; 
 int /*<<< orphan*/  PHY_SwChnl8192C ; 
 int /*<<< orphan*/  c2h_handler_8192c ; 
 int /*<<< orphan*/  c2h_id_filter_ccx_8192c ; 
 int /*<<< orphan*/  hal_notch_filter_8192c ; 
 int /*<<< orphan*/  hal_reset_security_engine_8192c ; 
 int /*<<< orphan*/  rtl8192c_Add_RateATid ; 
 int /*<<< orphan*/  rtl8192c_EFUSE_GetEfuseDefinition ; 
 int /*<<< orphan*/  rtl8192c_EfuseGetCurrentSize ; 
 int /*<<< orphan*/  rtl8192c_EfusePowerSwitch ; 
 int /*<<< orphan*/  rtl8192c_Efuse_PgPacketRead ; 
 int /*<<< orphan*/  rtl8192c_Efuse_PgPacketWrite ; 
 int /*<<< orphan*/  rtl8192c_Efuse_WordEnableDataWrite ; 
 int /*<<< orphan*/  rtl8192c_HalDmWatchDog ; 
 int /*<<< orphan*/  rtl8192c_PHY_QueryBBReg ; 
 int /*<<< orphan*/  rtl8192c_PHY_QueryRFReg ; 
 int /*<<< orphan*/  rtl8192c_PHY_SetBBReg ; 
 int /*<<< orphan*/  rtl8192c_PHY_SetRFReg ; 
 int /*<<< orphan*/  rtl8192c_ReadEFuse ; 
 int /*<<< orphan*/  rtl8192c_deinit_dm_priv ; 
 int /*<<< orphan*/  rtl8192c_free_hal_data ; 
 int /*<<< orphan*/  rtl8192c_init_dm_priv ; 
 int /*<<< orphan*/  rtl8192c_read_chip_version ; 

void rtl8192c_set_hal_ops(struct hal_ops *pHalFunc)
{
	pHalFunc->free_hal_data = &rtl8192c_free_hal_data;

	pHalFunc->dm_init = &rtl8192c_init_dm_priv;
	pHalFunc->dm_deinit = &rtl8192c_deinit_dm_priv;
	pHalFunc->read_chip_version = &rtl8192c_read_chip_version;

	pHalFunc->set_bwmode_handler = &PHY_SetBWMode8192C;
	pHalFunc->set_channel_handler = &PHY_SwChnl8192C;

	pHalFunc->hal_dm_watchdog = &rtl8192c_HalDmWatchDog;

	pHalFunc->Add_RateATid = &rtl8192c_Add_RateATid;

#ifdef CONFIG_ANTENNA_DIVERSITY
	pHalFunc->AntDivBeforeLinkHandler = &SwAntDivBeforeLink8192C;
	pHalFunc->AntDivCompareHandler = &SwAntDivCompare8192C;
#endif

	pHalFunc->read_bbreg = &rtl8192c_PHY_QueryBBReg;
	pHalFunc->write_bbreg = &rtl8192c_PHY_SetBBReg;
	pHalFunc->read_rfreg = &rtl8192c_PHY_QueryRFReg;
	pHalFunc->write_rfreg = &rtl8192c_PHY_SetRFReg;

	//Efuse related function
	pHalFunc->EfusePowerSwitch = &rtl8192c_EfusePowerSwitch;
	pHalFunc->ReadEFuse = &rtl8192c_ReadEFuse;
	pHalFunc->EFUSEGetEfuseDefinition = &rtl8192c_EFUSE_GetEfuseDefinition;
	pHalFunc->EfuseGetCurrentSize = &rtl8192c_EfuseGetCurrentSize;
	pHalFunc->Efuse_PgPacketRead = &rtl8192c_Efuse_PgPacketRead;
	pHalFunc->Efuse_PgPacketWrite = &rtl8192c_Efuse_PgPacketWrite;
	pHalFunc->Efuse_WordEnableDataWrite = &rtl8192c_Efuse_WordEnableDataWrite;

#ifdef DBG_CONFIG_ERROR_DETECT
	pHalFunc->sreset_init_value = &sreset_init_value;
	pHalFunc->sreset_reset_value = &sreset_reset_value;	
	pHalFunc->silentreset = &sreset_reset;
	pHalFunc->sreset_xmit_status_check = &rtl8192c_sreset_xmit_status_check;
	pHalFunc->sreset_linked_status_check  = &rtl8192c_sreset_linked_status_check;
	pHalFunc->sreset_get_wifi_status  = &sreset_get_wifi_status;
	pHalFunc->sreset_inprogress= &sreset_inprogress;
#endif

#ifdef CONFIG_IOL
	pHalFunc->IOL_exec_cmds_sync = &rtl8192c_IOL_exec_cmds_sync;
#endif
	pHalFunc->hal_notch_filter = &hal_notch_filter_8192c;
	pHalFunc->hal_reset_security_engine = hal_reset_security_engine_8192c;

	pHalFunc->c2h_handler = c2h_handler_8192c;
	pHalFunc->c2h_id_filter_ccx = c2h_id_filter_ccx_8192c;
}