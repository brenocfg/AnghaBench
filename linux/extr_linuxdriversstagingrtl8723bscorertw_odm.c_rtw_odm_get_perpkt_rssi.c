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
struct TYPE_2__ {int /*<<< orphan*/  RSSI_B; int /*<<< orphan*/  RSSI_A; int /*<<< orphan*/  RxRate; } ;
struct hal_com_data {TYPE_1__ odmpriv; } ;
struct adapter {int dummy; } ;
typedef  TYPE_1__ DM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X_SEL_NL (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  HDATA_RATE (int /*<<< orphan*/ ) ; 

void rtw_odm_get_perpkt_rssi(void *sel, struct adapter *adapter)
{
	struct hal_com_data *hal_data = GET_HAL_DATA(adapter);
	DM_ODM_T *odm = &hal_data->odmpriv;

	DBG_871X_SEL_NL(sel, "RxRate = %s, RSSI_A = %d(%%), RSSI_B = %d(%%)\n",
			HDATA_RATE(odm->RxRate), odm->RSSI_A, odm->RSSI_B);
}