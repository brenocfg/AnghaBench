#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u32 ;
struct sta_info {size_t ra_mask; int raid; int init_rate; } ;
struct TYPE_13__ {int /*<<< orphan*/  SupportedRates; } ;
struct mlme_ext_info {TYPE_1__* FW_sta_info; int /*<<< orphan*/  HT_caps; int /*<<< orphan*/  HT_enable; TYPE_2__ network; } ;
struct mlme_ext_priv {int cur_wireless_mode; struct mlme_ext_info mlmext_info; } ;
struct dm_priv {int* INIDATA_RATE; } ;
typedef  TYPE_2__ WLAN_BSSID_EX ;
struct TYPE_15__ {scalar_t__ fw_ractrl; struct dm_priv dmpriv; } ;
struct TYPE_14__ {struct mlme_ext_priv mlmeextpriv; } ;
struct TYPE_12__ {int /*<<< orphan*/  SupportedRates; struct sta_info* psta; } ;
typedef  TYPE_3__* PADAPTER ;
typedef  TYPE_4__ HAL_DATA_TYPE ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DBG_871X (char*,size_t,int) ; 
 TYPE_4__* GET_HAL_DATA (TYPE_3__*) ; 
 size_t NUM_STA ; 
 scalar_t__ REG_INIDATA_RATE_SEL ; 
 int WIRELESS_11B ; 
 int WIRELESS_11G ; 
 int _FALSE ; 
 scalar_t__ _TRUE ; 
 int get_highest_rate_idx (size_t) ; 
 int judge_network_type (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int networktype_to_raid (int) ; 
 int /*<<< orphan*/  rtl8192c_set_raid_cmd (TYPE_3__*,size_t,int) ; 
 int rtw_get_rateset_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  support_short_GI (TYPE_3__*,int /*<<< orphan*/ *) ; 
 size_t update_MSC_rate (int /*<<< orphan*/ *) ; 
 size_t update_basic_rate (int /*<<< orphan*/ ,int) ; 
 size_t update_supported_rate (int /*<<< orphan*/ ,int) ; 

void UpdateHalRAMask8192CUsb(PADAPTER padapter, u32 mac_id)
{
	//volatile unsigned int result;
	u8	init_rate=0;
	u8	networkType, raid;	
	u32	mask;
	u8	shortGIrate = _FALSE;
	int	supportRateNum = 0;
	struct sta_info	*psta;
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	struct dm_priv	*pdmpriv = &pHalData->dmpriv;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	WLAN_BSSID_EX 		*cur_network = &(pmlmeinfo->network);
#ifdef CONFIG_BT_COEXIST
	struct btcoexist_priv	*pbtpriv = &(pHalData->bt_coexist);
#endif

	if (mac_id >= NUM_STA) //CAM_SIZE
	{
		return;
	}

	psta = pmlmeinfo->FW_sta_info[mac_id].psta;
	if(psta == NULL)
	{
		return;
	}

	switch (mac_id)
	{
		case 0:// for infra mode
#ifdef CONFIG_CONCURRENT_MODE
		case 2:// first station uses macid=0, second station uses macid=2
#endif
			supportRateNum = rtw_get_rateset_len(cur_network->SupportedRates);
			networkType = judge_network_type(padapter, cur_network->SupportedRates, supportRateNum) & 0xf;
			//pmlmeext->cur_wireless_mode = networkType;
			raid = networktype_to_raid(networkType);
						
			mask = update_supported_rate(cur_network->SupportedRates, supportRateNum);
			mask |= (pmlmeinfo->HT_enable)? update_MSC_rate(&(pmlmeinfo->HT_caps)): 0;
			mask |= ((raid<<28)&0xf0000000);
			
			if (support_short_GI(padapter, &(pmlmeinfo->HT_caps)))
			{
				shortGIrate = _TRUE;
			}
			
			break;

		case 1://for broadcast/multicast
			supportRateNum = rtw_get_rateset_len(pmlmeinfo->FW_sta_info[mac_id].SupportedRates);
			if(pmlmeext->cur_wireless_mode & WIRELESS_11B)
				networkType = WIRELESS_11B;
			else
				networkType = WIRELESS_11G;
			raid = networktype_to_raid(networkType);

			mask = update_basic_rate(cur_network->SupportedRates, supportRateNum);
			mask |= ((raid<<28)&0xf0000000);

			break;

		default: //for each sta in IBSS
#ifdef CONFIG_TDLS
			if(psta->tdls_sta_state & TDLS_LINKED_STATE)
			{
				shortGIrate = update_sgi_tdls(padapter, psta);
				mask = update_mask_tdls(padapter, psta);
				raid = mask>>28;
				break;
			}
			else
#endif //CONFIG_TDLS
			{
				supportRateNum = rtw_get_rateset_len(pmlmeinfo->FW_sta_info[mac_id].SupportedRates);
				networkType = judge_network_type(padapter, pmlmeinfo->FW_sta_info[mac_id].SupportedRates, supportRateNum) & 0xf;
				//pmlmeext->cur_wireless_mode = networkType;
				raid = networktype_to_raid(networkType);
				
				mask = update_supported_rate(cur_network->SupportedRates, supportRateNum);
				mask |= ((raid<<28)&0xf0000000);

				//todo: support HT in IBSS
				
				break;
			}
	}
	
#ifdef CONFIG_BT_COEXIST
	if( (pbtpriv->BT_Coexist) &&
		(pbtpriv->BT_CoexistType == BT_CSR_BC4) &&
		(pbtpriv->BT_CUR_State) &&
		(pbtpriv->BT_Ant_isolation) &&
		((pbtpriv->BT_Service==BT_SCO)||
		(pbtpriv->BT_Service==BT_Busy)) )
		mask &= 0xffffcfc0;
	else		
#endif
		mask &=0xffffffff;
	
	
	init_rate = get_highest_rate_idx(mask)&0x3f;
	
	if(pHalData->fw_ractrl == _TRUE)
	{
		u8 arg = 0;

		//arg = (cam_idx-4)&0x1f;//MACID
		arg = mac_id&0x1f;//MACID
		
		arg |= BIT(7);
		
		if (shortGIrate==_TRUE)
			arg |= BIT(5);

		DBG_871X("update raid entry, mask=0x%x, arg=0x%x\n", mask, arg);
		psta->ra_mask=mask;
#ifdef CONFIG_INTEL_PROXIM
		if(padapter->proximity.proxim_on ==_TRUE){
			arg &= ~BIT(6);
		}
		else {
			arg |= BIT(6);
		}
#endif //CONFIG_INTEL_PROXIM
		rtl8192c_set_raid_cmd(padapter, mask, arg);	
		
	}
	else
	{
		if (shortGIrate==_TRUE)
			init_rate |= BIT(6);

		rtw_write8(padapter, (REG_INIDATA_RATE_SEL+mac_id), init_rate);		
	}


	//set ra_id
	psta->raid = raid;
	psta->init_rate = init_rate;

	//set correct initial date rate for each mac_id
	pdmpriv->INIDATA_RATE[mac_id] = init_rate;
}