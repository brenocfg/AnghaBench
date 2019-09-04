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
struct TYPE_3__ {int /*<<< orphan*/  GetDeltaSwingTable; int /*<<< orphan*/  PHY_LCCalibrate; int /*<<< orphan*/  DoIQK; int /*<<< orphan*/  ODM_TxPwrTrackSetPwr; int /*<<< orphan*/  ThermalRegAddr; int /*<<< orphan*/  RfPathCount; int /*<<< orphan*/  AverageThermalNum; int /*<<< orphan*/  Threshold_IQK; int /*<<< orphan*/  SwingTableSize_OFDM; int /*<<< orphan*/  SwingTableSize_CCK; } ;
typedef  TYPE_1__* PTXPWRTRACK_CFG ;

/* Variables and functions */
 int /*<<< orphan*/  AVG_THERMAL_NUM_8723B ; 
 int /*<<< orphan*/  CCK_TABLE_SIZE ; 
 int /*<<< orphan*/  DoIQK_8723B ; 
 int /*<<< orphan*/  GetDeltaSwingTable_8723B ; 
 int /*<<< orphan*/  IQK_THRESHOLD ; 
 int /*<<< orphan*/  MAX_PATH_NUM_8723B ; 
 int /*<<< orphan*/  ODM_TxPwrTrackSetPwr_8723B ; 
 int /*<<< orphan*/  OFDM_TABLE_SIZE ; 
 int /*<<< orphan*/  PHY_LCCalibrate_8723B ; 
 int /*<<< orphan*/  RF_T_METER_8723B ; 

void ConfigureTxpowerTrack_8723B(PTXPWRTRACK_CFG pConfig)
{
	pConfig->SwingTableSize_CCK = CCK_TABLE_SIZE;
	pConfig->SwingTableSize_OFDM = OFDM_TABLE_SIZE;
	pConfig->Threshold_IQK = IQK_THRESHOLD;
	pConfig->AverageThermalNum = AVG_THERMAL_NUM_8723B;
	pConfig->RfPathCount = MAX_PATH_NUM_8723B;
	pConfig->ThermalRegAddr = RF_T_METER_8723B;

	pConfig->ODM_TxPwrTrackSetPwr = ODM_TxPwrTrackSetPwr_8723B;
	pConfig->DoIQK = DoIQK_8723B;
	pConfig->PHY_LCCalibrate = PHY_LCCalibrate_8723B;
	pConfig->GetDeltaSwingTable = GetDeltaSwingTable_8723B;
}