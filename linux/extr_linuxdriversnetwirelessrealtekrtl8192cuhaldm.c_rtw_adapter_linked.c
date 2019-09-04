#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlme_priv {int dummy; } ;
struct TYPE_4__ {int asoc_sta_count; } ;
struct TYPE_5__ {TYPE_1__ stapriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int WIFI_ADHOC_MASTER_STATE ; 
 int WIFI_ADHOC_STATE ; 
 int WIFI_AP_STATE ; 
 int _FALSE ; 
 int _FW_LINKED ; 
 int _TRUE ; 
 int check_fwstate (struct mlme_priv*,int) ; 

bool rtw_adapter_linked(_adapter *adapter)
{
	bool linked = _FALSE;
	struct mlme_priv	*mlmepriv = &adapter->mlmepriv;

	if(	(check_fwstate(mlmepriv, WIFI_AP_STATE) == _TRUE) ||
		(check_fwstate(mlmepriv, WIFI_ADHOC_STATE|WIFI_ADHOC_MASTER_STATE) == _TRUE))
	{				
		if(adapter->stapriv.asoc_sta_count > 2)
			linked = _TRUE;
	}
	else{//Station mode
		if(check_fwstate(mlmepriv, _FW_LINKED)== _TRUE)
			linked = _TRUE;
	}

	return linked;
}