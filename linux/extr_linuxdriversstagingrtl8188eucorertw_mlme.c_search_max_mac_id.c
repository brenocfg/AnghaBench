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
typedef  size_t u8 ;
struct mlme_ext_info {TYPE_1__* FW_sta_info; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 size_t IBSS_START_MAC_ID ; 
 size_t NUM_STA ; 

__attribute__((used)) static u8 search_max_mac_id(struct adapter *padapter)
{
	u8 mac_id;
#if defined(CONFIG_88EU_AP_MODE)
	u8 aid;
	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	struct sta_priv *pstapriv = &padapter->stapriv;
#endif
	struct mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

#if defined(CONFIG_88EU_AP_MODE)
	if (check_fwstate(pmlmepriv, WIFI_AP_STATE)) {
		for (aid = pstapriv->max_num_sta; aid > 0; aid--) {
			if (pstapriv->sta_aid[aid-1])
				break;
		}
		mac_id = aid + 1;
	} else
#endif
	{/* adhoc  id =  31~2 */
		for (mac_id = NUM_STA-1; mac_id >= IBSS_START_MAC_ID; mac_id--) {
			if (pmlmeinfo->FW_sta_info[mac_id].status == 1)
				break;
		}
	}
	return mac_id;
}