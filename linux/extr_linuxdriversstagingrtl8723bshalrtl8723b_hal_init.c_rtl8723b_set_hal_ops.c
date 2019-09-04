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
struct hal_ops {int /*<<< orphan*/ * fill_h2c_cmd; int /*<<< orphan*/  c2h_id_filter_ccx; int /*<<< orphan*/  c2h_handler; int /*<<< orphan*/ * hal_notch_filter; int /*<<< orphan*/ * xmit_thread_handler; int /*<<< orphan*/ * SetHalODMVarHandler; int /*<<< orphan*/ * GetHalODMVarHandler; int /*<<< orphan*/ * Efuse_PgPacketWrite_BT; int /*<<< orphan*/ * Efuse_WordEnableDataWrite; int /*<<< orphan*/ * Efuse_PgPacketWrite; int /*<<< orphan*/ * Efuse_PgPacketRead; int /*<<< orphan*/ * EfuseGetCurrentSize; int /*<<< orphan*/ * EFUSEGetEfuseDefinition; int /*<<< orphan*/ * ReadEFuse; int /*<<< orphan*/ * EfusePowerSwitch; int /*<<< orphan*/ * BTEfusePowerSwitch; int /*<<< orphan*/ * write_rfreg; int /*<<< orphan*/ * read_rfreg; int /*<<< orphan*/ * write_bbreg; int /*<<< orphan*/ * read_bbreg; int /*<<< orphan*/ * cancel_thread; int /*<<< orphan*/ * run_thread; int /*<<< orphan*/ * Add_RateATid; int /*<<< orphan*/ * SetBeaconRelatedRegistersHandler; int /*<<< orphan*/ * hal_dm_watchdog_in_lps; int /*<<< orphan*/ * hal_dm_watchdog; int /*<<< orphan*/ * get_tx_power_level_handler; int /*<<< orphan*/ * set_tx_power_level_handler; int /*<<< orphan*/ * set_chnl_bw_handler; int /*<<< orphan*/ * set_channel_handler; int /*<<< orphan*/ * set_bwmode_handler; int /*<<< orphan*/ * UpdateRAMaskHandler; int /*<<< orphan*/ * read_chip_version; int /*<<< orphan*/ * dm_init; int /*<<< orphan*/ * free_hal_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FillH2CCmd8723B ; 
 int /*<<< orphan*/  Hal_BT_EfusePowerSwitch ; 
 int /*<<< orphan*/  Hal_EfuseGetCurrentSize ; 
 int /*<<< orphan*/  Hal_EfusePgPacketRead ; 
 int /*<<< orphan*/  Hal_EfusePgPacketWrite ; 
 int /*<<< orphan*/  Hal_EfusePgPacketWrite_BT ; 
 int /*<<< orphan*/  Hal_EfusePowerSwitch ; 
 int /*<<< orphan*/  Hal_EfuseWordEnableDataWrite ; 
 int /*<<< orphan*/  Hal_GetEfuseDefinition ; 
 int /*<<< orphan*/  Hal_ReadEFuse ; 
 int /*<<< orphan*/  PHY_GetTxPowerLevel8723B ; 
 int /*<<< orphan*/  PHY_QueryBBReg_8723B ; 
 int /*<<< orphan*/  PHY_QueryRFReg_8723B ; 
 int /*<<< orphan*/  PHY_SetBBReg_8723B ; 
 int /*<<< orphan*/  PHY_SetBWMode8723B ; 
 int /*<<< orphan*/  PHY_SetRFReg_8723B ; 
 int /*<<< orphan*/  PHY_SetSwChnlBWMode8723B ; 
 int /*<<< orphan*/  PHY_SetTxPowerLevel8723B ; 
 int /*<<< orphan*/  PHY_SwChnl8723B ; 
 int /*<<< orphan*/  UpdateHalRAMask8723B ; 
 int /*<<< orphan*/  c2h_handler_8723b ; 
 int /*<<< orphan*/  c2h_id_filter_ccx_8723b ; 
 int /*<<< orphan*/  hal_notch_filter_8723b ; 
 int /*<<< orphan*/  hal_xmit_handler ; 
 int /*<<< orphan*/  rtl8723b_Add_RateATid ; 
 int /*<<< orphan*/  rtl8723b_GetHalODMVar ; 
 int /*<<< orphan*/  rtl8723b_HalDmWatchDog ; 
 int /*<<< orphan*/  rtl8723b_HalDmWatchDog_in_LPS ; 
 int /*<<< orphan*/  rtl8723b_SetBeaconRelatedRegisters ; 
 int /*<<< orphan*/  rtl8723b_SetHalODMVar ; 
 int /*<<< orphan*/  rtl8723b_free_hal_data ; 
 int /*<<< orphan*/  rtl8723b_init_dm_priv ; 
 int /*<<< orphan*/  rtl8723b_read_chip_version ; 
 int /*<<< orphan*/  rtl8723b_start_thread ; 
 int /*<<< orphan*/  rtl8723b_stop_thread ; 

void rtl8723b_set_hal_ops(struct hal_ops *pHalFunc)
{
	pHalFunc->free_hal_data = &rtl8723b_free_hal_data;

	pHalFunc->dm_init = &rtl8723b_init_dm_priv;

	pHalFunc->read_chip_version = &rtl8723b_read_chip_version;

	pHalFunc->UpdateRAMaskHandler = &UpdateHalRAMask8723B;

	pHalFunc->set_bwmode_handler = &PHY_SetBWMode8723B;
	pHalFunc->set_channel_handler = &PHY_SwChnl8723B;
	pHalFunc->set_chnl_bw_handler = &PHY_SetSwChnlBWMode8723B;

	pHalFunc->set_tx_power_level_handler = &PHY_SetTxPowerLevel8723B;
	pHalFunc->get_tx_power_level_handler = &PHY_GetTxPowerLevel8723B;

	pHalFunc->hal_dm_watchdog = &rtl8723b_HalDmWatchDog;
	pHalFunc->hal_dm_watchdog_in_lps = &rtl8723b_HalDmWatchDog_in_LPS;


	pHalFunc->SetBeaconRelatedRegistersHandler = &rtl8723b_SetBeaconRelatedRegisters;

	pHalFunc->Add_RateATid = &rtl8723b_Add_RateATid;

	pHalFunc->run_thread = &rtl8723b_start_thread;
	pHalFunc->cancel_thread = &rtl8723b_stop_thread;

	pHalFunc->read_bbreg = &PHY_QueryBBReg_8723B;
	pHalFunc->write_bbreg = &PHY_SetBBReg_8723B;
	pHalFunc->read_rfreg = &PHY_QueryRFReg_8723B;
	pHalFunc->write_rfreg = &PHY_SetRFReg_8723B;

	/*  Efuse related function */
	pHalFunc->BTEfusePowerSwitch = &Hal_BT_EfusePowerSwitch;
	pHalFunc->EfusePowerSwitch = &Hal_EfusePowerSwitch;
	pHalFunc->ReadEFuse = &Hal_ReadEFuse;
	pHalFunc->EFUSEGetEfuseDefinition = &Hal_GetEfuseDefinition;
	pHalFunc->EfuseGetCurrentSize = &Hal_EfuseGetCurrentSize;
	pHalFunc->Efuse_PgPacketRead = &Hal_EfusePgPacketRead;
	pHalFunc->Efuse_PgPacketWrite = &Hal_EfusePgPacketWrite;
	pHalFunc->Efuse_WordEnableDataWrite = &Hal_EfuseWordEnableDataWrite;
	pHalFunc->Efuse_PgPacketWrite_BT = &Hal_EfusePgPacketWrite_BT;

	pHalFunc->GetHalODMVarHandler = &rtl8723b_GetHalODMVar;
	pHalFunc->SetHalODMVarHandler = &rtl8723b_SetHalODMVar;

	pHalFunc->xmit_thread_handler = &hal_xmit_handler;
	pHalFunc->hal_notch_filter = &hal_notch_filter_8723b;

	pHalFunc->c2h_handler = c2h_handler_8723b;
	pHalFunc->c2h_id_filter_ccx = c2h_id_filter_ccx_8723b;

	pHalFunc->fill_h2c_cmd = &FillH2CCmd8723B;
}