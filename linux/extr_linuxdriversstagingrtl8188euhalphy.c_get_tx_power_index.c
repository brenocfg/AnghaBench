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
typedef  size_t u8 ;
struct hal_data_8188e {size_t** Index24G_CCK_Base; size_t** Index24G_BW40_Base; size_t** OFDM_24G_Diff; size_t** BW20_24G_Diff; } ;
struct adapter {struct hal_data_8188e* HalData; } ;

/* Variables and functions */
 size_t RF_PATH_A ; 
 size_t RF_PATH_B ; 

__attribute__((used)) static void get_tx_power_index(struct adapter *adapt, u8 channel, u8 *cck_pwr,
			       u8 *ofdm_pwr, u8 *bw20_pwr, u8 *bw40_pwr)
{
	struct hal_data_8188e *hal_data = adapt->HalData;
	u8 index = (channel - 1);
	u8 TxCount = 0, path_nums;

	path_nums = 1;

	for (TxCount = 0; TxCount < path_nums; TxCount++) {
		if (TxCount == RF_PATH_A) {
			cck_pwr[TxCount] = hal_data->Index24G_CCK_Base[TxCount][index];
			ofdm_pwr[TxCount] = hal_data->Index24G_BW40_Base[RF_PATH_A][index]+
					    hal_data->OFDM_24G_Diff[TxCount][RF_PATH_A];

			bw20_pwr[TxCount] = hal_data->Index24G_BW40_Base[RF_PATH_A][index]+
					    hal_data->BW20_24G_Diff[TxCount][RF_PATH_A];
			bw40_pwr[TxCount] = hal_data->Index24G_BW40_Base[TxCount][index];
		} else if (TxCount == RF_PATH_B) {
			cck_pwr[TxCount] = hal_data->Index24G_CCK_Base[TxCount][index];
			ofdm_pwr[TxCount] = hal_data->Index24G_BW40_Base[RF_PATH_A][index]+
			hal_data->BW20_24G_Diff[RF_PATH_A][index]+
			hal_data->BW20_24G_Diff[TxCount][index];

			bw20_pwr[TxCount] = hal_data->Index24G_BW40_Base[RF_PATH_A][index]+
			hal_data->BW20_24G_Diff[TxCount][RF_PATH_A]+
			hal_data->BW20_24G_Diff[TxCount][index];
			bw40_pwr[TxCount] = hal_data->Index24G_BW40_Base[TxCount][index];
		}
	}
}