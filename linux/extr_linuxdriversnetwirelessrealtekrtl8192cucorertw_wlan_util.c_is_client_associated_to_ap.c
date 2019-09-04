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
struct mlme_ext_info {int state; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_3__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int WIFI_FW_ASSOC_SUCCESS ; 
 int WIFI_FW_STATION_STATE ; 
 int _FAIL ; 
 int _TRUE ; 

int is_client_associated_to_ap(_adapter *padapter)
{
	struct mlme_ext_priv	*pmlmeext;
	struct mlme_ext_info	*pmlmeinfo;

	if(!padapter)
		return _FAIL;

	pmlmeext = &padapter->mlmeextpriv;
	pmlmeinfo = &(pmlmeext->mlmext_info);
	
	if ((pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS) && ((pmlmeinfo->state&0x03) == WIFI_FW_STATION_STATE))
	{
		return _TRUE;
	}
	else
	{
		return _FAIL;
	}
}