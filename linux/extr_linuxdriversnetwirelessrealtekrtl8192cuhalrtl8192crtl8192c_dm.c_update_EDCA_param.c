#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  size_t u32 ;
struct xmit_priv {int tx_bytes; int last_tx_bytes; } ;
struct registry_priv {int wifi_spec; } ;
struct recv_priv {int rx_bytes; int last_rx_bytes; } ;
struct mlme_ext_info {scalar_t__ HT_enable; size_t assoc_AP_vendor; } ;
struct mlme_ext_priv {int cur_wireless_mode; struct mlme_ext_info mlmext_info; } ;
struct dm_priv {size_t prv_traffic_idx; } ;
struct TYPE_7__ {struct mlme_ext_priv mlmeextpriv; struct registry_priv registrypriv; struct recv_priv recvpriv; struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_8__ {struct dm_priv dmpriv; } ;
typedef  TYPE_2__* PHAL_DATA_TYPE ;

/* Variables and functions */
 size_t DOWN_LINK ; 
 size_t** EDCAParam ; 
 TYPE_2__* GET_HAL_DATA (TYPE_1__*) ; 
 int /*<<< orphan*/  REG_EDCA_BE_PARAM ; 
 size_t UP_LINK ; 
 int WIRELESS_11BG ; 
 int WIRELESS_11G ; 
 int WIRELESS_11_24N ; 
 size_t airgocapAP ; 
 size_t atherosAP ; 
 size_t ciscoAP ; 
 size_t maxAP ; 
 size_t ralinkAP ; 
 int /*<<< orphan*/  rtw_write32 (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 size_t unknownAP ; 

__attribute__((used)) static void update_EDCA_param(_adapter *padapter)
{
	u32 	trafficIndex;
	u32	edca_param;
	u64	cur_tx_bytes = 0;
	u64	cur_rx_bytes = 0;
	PHAL_DATA_TYPE		pHalData = GET_HAL_DATA(padapter);
	struct dm_priv		*pdmpriv = &pHalData->dmpriv;
	struct xmit_priv		*pxmitpriv = &(padapter->xmitpriv);
	struct recv_priv		*precvpriv = &(padapter->recvpriv);
	struct registry_priv	*pregpriv = &padapter->registrypriv;
	struct mlme_ext_priv	*pmlmeext = &(padapter->mlmeextpriv);
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	
#ifdef CONFIG_BT_COEXIST
	struct btcoexist_priv	*pbtpriv = &(pHalData->bt_coexist);	
	u8	bbtchange = _FALSE;
#endif
	

	//DBG_871X("%s\n", __FUNCTION__);

	//associated AP
	if ((pregpriv->wifi_spec == 1) || (pmlmeinfo->HT_enable == 0))
	{
		return;
	}
	
	if (pmlmeinfo->assoc_AP_vendor >= maxAP)
	{
		return;
	}

	cur_tx_bytes = pxmitpriv->tx_bytes - pxmitpriv->last_tx_bytes;
	cur_rx_bytes = precvpriv->rx_bytes - precvpriv->last_rx_bytes;

	//traffic, TX or RX
	if((pmlmeinfo->assoc_AP_vendor == ralinkAP)||(pmlmeinfo->assoc_AP_vendor == atherosAP))
	{
		if (cur_tx_bytes > (cur_rx_bytes << 2))
		{ // Uplink TP is present.
			trafficIndex = UP_LINK; 
		}
		else
		{ // Balance TP is present.
			trafficIndex = DOWN_LINK;
		}
	}
	else
	{
		if (cur_rx_bytes > (cur_tx_bytes << 2))
		{ // Downlink TP is present.
			trafficIndex = DOWN_LINK;
		}
		else
		{ // Balance TP is present.
			trafficIndex = UP_LINK;
		}
	}

#ifdef CONFIG_BT_COEXIST
	if(pbtpriv->BT_Coexist)
	{
		if( (pbtpriv->BT_EDCA[UP_LINK]!=0) ||  (pbtpriv->BT_EDCA[DOWN_LINK]!=0))
		{
			bbtchange = _TRUE;
		}
	}
#endif

	if (pdmpriv->prv_traffic_idx != trafficIndex)
	{
#if 0
#ifdef CONFIG_BT_COEXIST
		if(_TRUE == bbtchange)		
			rtw_write32(padapter, REG_EDCA_BE_PARAM, pbtpriv->BT_EDCA[trafficIndex]);		
		else
#endif
		//adjust EDCA parameter for BE queue
		//fire_write_MAC_cmd(padapter, EDCA_BE_PARAM, EDCAParam[pmlmeinfo->assoc_AP_vendor][trafficIndex]);
		rtw_write32(padapter, REG_EDCA_BE_PARAM, EDCAParam[pmlmeinfo->assoc_AP_vendor][trafficIndex]);

#else
		if((pmlmeinfo->assoc_AP_vendor == ciscoAP) && (pmlmeext->cur_wireless_mode & WIRELESS_11_24N))
		{
			edca_param = EDCAParam[pmlmeinfo->assoc_AP_vendor][trafficIndex];
		}
		else if((pmlmeinfo->assoc_AP_vendor == airgocapAP) &&
			((pmlmeext->cur_wireless_mode == WIRELESS_11G) ||(pmlmeext->cur_wireless_mode == WIRELESS_11BG)))
		{
			edca_param = EDCAParam[pmlmeinfo->assoc_AP_vendor][trafficIndex];
		}
		else
		{
			edca_param = EDCAParam[unknownAP][trafficIndex];
		}

#ifdef CONFIG_BT_COEXIST
		if(_TRUE == bbtchange)		
			edca_param = pbtpriv->BT_EDCA[trafficIndex];
#endif

		rtw_write32(padapter, REG_EDCA_BE_PARAM, edca_param);
#endif
		pdmpriv->prv_traffic_idx = trafficIndex;
	}
	
//exit_update_EDCA_param:	

	pxmitpriv->last_tx_bytes = pxmitpriv->tx_bytes;
	precvpriv->last_rx_bytes = precvpriv->rx_bytes;

	return;
}