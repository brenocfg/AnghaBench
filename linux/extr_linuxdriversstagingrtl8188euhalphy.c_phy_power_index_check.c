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
typedef  void* u8 ;
struct hal_data_8188e {void* CurrentBW4024GTxPwrIdx; void* CurrentBW2024GTxPwrIdx; void* CurrentOfdm24GTxPwrIdx; void* CurrentCckTxPwrIdx; } ;
struct adapter {struct hal_data_8188e* HalData; } ;

/* Variables and functions */

__attribute__((used)) static void phy_power_index_check(struct adapter *adapt, u8 channel,
				  u8 *cck_pwr, u8 *ofdm_pwr, u8 *bw20_pwr,
				  u8 *bw40_pwr)
{
	struct hal_data_8188e *hal_data = adapt->HalData;

	hal_data->CurrentCckTxPwrIdx = cck_pwr[0];
	hal_data->CurrentOfdm24GTxPwrIdx = ofdm_pwr[0];
	hal_data->CurrentBW2024GTxPwrIdx = bw20_pwr[0];
	hal_data->CurrentBW4024GTxPwrIdx = bw40_pwr[0];
}