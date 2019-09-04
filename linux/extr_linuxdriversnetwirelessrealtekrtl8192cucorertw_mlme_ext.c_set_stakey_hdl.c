#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct sta_priv {int dummy; } ;
struct sta_info {int mac_id; } ;
struct set_stakey_parm {int algorithm; int /*<<< orphan*/  key; int /*<<< orphan*/ * addr; int /*<<< orphan*/  id; } ;
struct mlme_ext_info {int state; int enc_algo; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_5__ {struct sta_priv stapriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 int H2C_REJECTED ; 
 int H2C_SUCCESS ; 
 int H2C_SUCCESS_RSP ; 
 int NUM_STA ; 
 int WIFI_FW_AP_STATE ; 
 int _NO_PRIVACY_ ; 
 int /*<<< orphan*/  clear_cam_entry (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_cam (TYPE_1__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u8 set_stakey_hdl(_adapter *padapter, u8 *pbuf)
{
	u16 ctrl=0;
	u8 cam_id=0;//cam_entry
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	struct set_stakey_parm	*pparm = (struct set_stakey_parm *)pbuf;
#ifdef CONFIG_TDLS
	struct tdls_info	*ptdlsinfo = &padapter->tdlsinfo;
	struct sta_priv	*pstapriv = &padapter->stapriv;
	struct sta_info	*psta;
#endif //CONFIG_TDLS

	//cam_entry:
	//0~3 for default key
	
	//for concurrent mode (ap+sta):
	//default key is disable, using sw encrypt/decrypt
	//cam_entry = 4 //for sta mode (macid=0)
	//cam_entry(macid+3) = 5 ~ N//for ap mode (aid=1~N, macid=2 ~N)

	//for concurrent mode (sta+sta):
	//default key is disable, using sw encrypt/decrypt
	//cam_entry = 4 //mapping to macid=0
	//cam_entry = 5 //mapping to macid=2

#ifdef CONFIG_CONCURRENT_MODE
	if((pmlmeinfo->state&0x03) == WIFI_FW_STATION_STATE)
	{
		struct sta_priv	*pstapriv = &padapter->stapriv;
		struct sta_info	*psta;
		
		psta = rtw_get_stainfo(pstapriv, pmlmeinfo->network.MacAddress);

		if(psta && psta->mac_id==2)
		{
			cam_id = 5;
		}
		else
		{
			cam_id = 4;
		}
/*		
		if(padapter->iface_type > PRIMARY_IFACE)
		{
			cam_id = 5;
		}
		else
		{
			cam_id = 4;
		}
*/		
	}	
#else
	cam_id = 4;
#endif


	if((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE)
	{
	
		struct sta_info *psta;
		struct sta_priv *pstapriv = &padapter->stapriv;

		if(pparm->algorithm == _NO_PRIVACY_)	// clear cam entry
		{
			clear_cam_entry(padapter, pparm->id);
			return H2C_SUCCESS_RSP;
		}
		
		psta = rtw_get_stainfo(pstapriv, pparm->addr);
		if(psta)
		{			
			ctrl = (BIT(15) | ((pparm->algorithm) << 2));

			DBG_871X("r871x_set_stakey_hdl(): enc_algorithm=%d\n", pparm->algorithm);

			if((psta->mac_id<1) || (psta->mac_id>(NUM_STA-4)))
			{
				DBG_871X("r871x_set_stakey_hdl():set_stakey failed, mac_id(aid)=%d\n", psta->mac_id);
				return H2C_REJECTED;
			}	
				 
			cam_id = (psta->mac_id + 3);//0~3 for default key, cmd_id=macid + 3, macid=aid+1;

			DBG_871X("Write CAM, mac_addr=%x:%x:%x:%x:%x:%x, cam_entry=%d\n", pparm->addr[0], 
						pparm->addr[1], pparm->addr[2], pparm->addr[3], pparm->addr[4],
						pparm->addr[5], cam_id);

			write_cam(padapter, cam_id, ctrl, pparm->addr, pparm->key);
	
			return H2C_SUCCESS_RSP;
		
		}
		else
		{
			DBG_871X("r871x_set_stakey_hdl(): sta has been free\n");
			return H2C_REJECTED;
		}
		
	}

	//below for sta mode
	
	if(pparm->algorithm == _NO_PRIVACY_)	// clear cam entry
	{
		clear_cam_entry(padapter, pparm->id);
		return H2C_SUCCESS;
	}
	
	ctrl = BIT(15) | ((pparm->algorithm) << 2);	
	
#ifdef CONFIG_TDLS
	if(ptdlsinfo->clear_cam!=0){
		clear_cam_entry(padapter, ptdlsinfo->clear_cam);
		ptdlsinfo->clear_cam=0;

		return H2C_SUCCESS;
	}

	psta = rtw_get_stainfo(pstapriv, pparm->addr);//Get TDLS Peer STA
	if( psta->tdls_sta_state&TDLS_LINKED_STATE ){
		write_cam(padapter, psta->mac_id, ctrl, pparm->addr, pparm->key);
	}
	else
#endif //CONFIG_TDLS	
	write_cam(padapter, cam_id, ctrl, pparm->addr, pparm->key);

	pmlmeinfo->enc_algo = pparm->algorithm;
	
	return H2C_SUCCESS;
}