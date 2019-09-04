#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct adapter {TYPE_1__* HalData; } ;
struct TYPE_2__ {scalar_t__ CurrentChannelBW; } ;

/* Variables and functions */
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 

__attribute__((used)) static void getpowerbase88e(struct adapter *adapt, u8 *pwr_level_ofdm,
			    u8 *pwr_level_bw20, u8 *pwr_level_bw40,
			    u8 channel, u32 *ofdmbase, u32 *mcs_base)
{
	u32 powerbase0, powerbase1;
	u8 i, powerlevel[2];

	for (i = 0; i < 2; i++) {
		powerbase0 = pwr_level_ofdm[i];

		powerbase0 = (powerbase0<<24) | (powerbase0<<16) |
			     (powerbase0<<8) | powerbase0;
		*(ofdmbase+i) = powerbase0;
	}
	/* Check HT20 to HT40 diff */
	if (adapt->HalData->CurrentChannelBW == HT_CHANNEL_WIDTH_20)
		powerlevel[0] = pwr_level_bw20[0];
	else
		powerlevel[0] = pwr_level_bw40[0];
	powerbase1 = powerlevel[0];
	powerbase1 = (powerbase1<<24) | (powerbase1<<16) |
		     (powerbase1<<8) | powerbase1;
	*mcs_base = powerbase1;
}