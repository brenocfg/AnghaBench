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
struct mlme_ext_info {TYPE_1__* FW_sta_info; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_5__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_2__ _adapter ;
struct TYPE_4__ {int status; scalar_t__ retry; } ;

/* Variables and functions */
 unsigned int IBSS_START_MAC_ID ; 
 unsigned int NUM_STA ; 

int allocate_fw_sta_entry(_adapter *padapter)
{
	unsigned int mac_id;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	
	for (mac_id = IBSS_START_MAC_ID; mac_id < NUM_STA; mac_id++)
	{
		if (pmlmeinfo->FW_sta_info[mac_id].status == 0)
		{
			pmlmeinfo->FW_sta_info[mac_id].status = 1;
			pmlmeinfo->FW_sta_info[mac_id].retry = 0;
			break;
		}
	}
	
	return mac_id;
}