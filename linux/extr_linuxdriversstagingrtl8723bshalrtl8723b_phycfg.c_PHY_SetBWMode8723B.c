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
struct hal_com_data {int /*<<< orphan*/  CurrentChannel; } ;
struct adapter {int dummy; } ;
typedef  enum CHANNEL_WIDTH { ____Placeholder_CHANNEL_WIDTH } CHANNEL_WIDTH ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  PHY_HandleSwChnlAndSetBW8723B (struct adapter*,int,int,int /*<<< orphan*/ ,int,unsigned char,unsigned char,int /*<<< orphan*/ ) ; 

void PHY_SetBWMode8723B(
	struct adapter *Adapter,
	enum CHANNEL_WIDTH Bandwidth, /*  20M or 40M */
	unsigned char Offset /*  Upper, Lower, or Don't care */
)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	PHY_HandleSwChnlAndSetBW8723B(Adapter, false, true, pHalData->CurrentChannel, Bandwidth, Offset, Offset, pHalData->CurrentChannel);
}