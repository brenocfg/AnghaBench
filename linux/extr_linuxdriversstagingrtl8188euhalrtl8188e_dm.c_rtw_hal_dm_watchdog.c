#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mlme_priv {int dummy; } ;
struct TYPE_4__ {int asoc_sta_count; } ;
struct adapter {int hw_init_completed; TYPE_2__* HalData; TYPE_1__ stapriv; struct mlme_priv mlmepriv; } ;
struct TYPE_6__ {int bLinked; } ;
struct TYPE_5__ {TYPE_3__ odmpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_DMWatchdog (TYPE_3__*) ; 
 int WIFI_ADHOC_MASTER_STATE ; 
 int WIFI_ADHOC_STATE ; 
 int WIFI_AP_STATE ; 
 int _FW_LINKED ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int) ; 

void rtw_hal_dm_watchdog(struct adapter *Adapter)
{
	u8 hw_init_completed = false;
	struct mlme_priv *pmlmepriv = NULL;
	u8 bLinked = false;

	hw_init_completed = Adapter->hw_init_completed;

	if (!hw_init_completed)
		goto skip_dm;

	/* ODM */
	pmlmepriv = &Adapter->mlmepriv;

	if ((check_fwstate(pmlmepriv, WIFI_AP_STATE)) ||
	    (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE |
			   WIFI_ADHOC_MASTER_STATE))) {
		if (Adapter->stapriv.asoc_sta_count > 2)
			bLinked = true;
	} else {/* Station mode */
		if (check_fwstate(pmlmepriv, _FW_LINKED))
			bLinked = true;
	}

	Adapter->HalData->odmpriv.bLinked = bLinked;
	ODM_DMWatchdog(&Adapter->HalData->odmpriv);
skip_dm:
	/*  Check GPIO to determine current RF on/off and Pbc status. */
	/*  Check Hardware Radio ON/OFF or not */
	return;
}