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
struct sreset_priv {int /*<<< orphan*/  Wifi_Error_Status; } ;
struct adapter {TYPE_1__* HalData; } ;
struct TYPE_2__ {struct sreset_priv srestpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIFI_STATUS_SUCCESS ; 

void rtw_hal_sreset_init(struct adapter *padapter)
{
	struct sreset_priv *psrtpriv = &padapter->HalData->srestpriv;

	psrtpriv->Wifi_Error_Status = WIFI_STATUS_SUCCESS;
}