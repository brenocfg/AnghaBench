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
typedef  int /*<<< orphan*/  _adapter ;
struct TYPE_3__ {int RegFwHwTxQCtrl; } ;
typedef  TYPE_1__ HAL_DATA_TYPE ;

/* Variables and functions */
 int BIT6 ; 
 TYPE_1__* GET_HAL_DATA (int /*<<< orphan*/ *) ; 
 scalar_t__ REG_FWHW_TXQ_CTRL ; 
 int /*<<< orphan*/  rtw_write8 (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void StopTxBeacon(_adapter *padapter)
{
	HAL_DATA_TYPE*	pHalData = GET_HAL_DATA(padapter);

	// 2010.03.01. Marked by tynli. No need to call workitem beacause we record the value
	// which should be read from register to a global variable.

	rtw_write8(padapter, REG_FWHW_TXQ_CTRL+2, (pHalData->RegFwHwTxQCtrl) & (~BIT6));
	pHalData->RegFwHwTxQCtrl &= (~BIT6);

	 //todo: CheckFwRsvdPageContent(Adapter);  // 2010.06.23. Added by tynli.

}