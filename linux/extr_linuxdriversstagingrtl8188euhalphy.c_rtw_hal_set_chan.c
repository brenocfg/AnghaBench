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
struct hal_data_8188e {void* CurrentChannel; } ;
struct adapter {int /*<<< orphan*/  bSurpriseRemoved; int /*<<< orphan*/  bDriverStopped; struct hal_data_8188e* HalData; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_sw_chnl_callback (struct adapter*,void*) ; 

void rtw_hal_set_chan(struct adapter *adapt, u8 channel)
{
	struct hal_data_8188e *hal_data = adapt->HalData;
	u8 tmpchannel = hal_data->CurrentChannel;

	if (channel == 0)
		channel = 1;

	hal_data->CurrentChannel = channel;

	if ((!adapt->bDriverStopped) && (!adapt->bSurpriseRemoved))
		phy_sw_chnl_callback(adapt, channel);
	else
		hal_data->CurrentChannel = tmpchannel;
}