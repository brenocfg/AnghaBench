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
struct rx_pkt_attrib {int hdrlen; int iv_len; int eth_type; int* dst; int* src; int /*<<< orphan*/  icv_len; scalar_t__ encrypt; } ;
struct TYPE_4__ {int len; struct rx_pkt_attrib attrib; TYPE_3__* adapter; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int u8 ;
typedef  int u16 ;
struct mlme_priv {int dummy; } ;
typedef  int ieee80211_snap_hdr ;
struct ethhdr {int dummy; } ;
typedef  int sint ;
struct TYPE_6__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_3__ _adapter ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SNAP_ETH_TYPE_APPLETALK_AARP ; 
 int /*<<< orphan*/  SNAP_ETH_TYPE_IPX ; 
 int SNAP_SIZE ; 
 int /*<<< orphan*/  WIFI_MP_STATE ; 
 scalar_t__ _FALSE ; 
 int _SUCCESS ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 scalar_t__ _rtw_memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _rtw_memcpy (int*,int*,int) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int* get_recvframe_data (union recv_frame*) ; 
 int* get_rxmem (union recv_frame*) ; 
 int htons (int) ; 
 int ntohs (unsigned short) ; 
 int* recvframe_pull (union recv_frame*,int) ; 
 int /*<<< orphan*/  recvframe_pull_tail (union recv_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_bridge_tunnel_header ; 
 int /*<<< orphan*/  rtw_rfc1042_header ; 

sint wlanhdr_to_ethhdr ( union recv_frame *precvframe)
{
	sint	rmv_len;
	u16	eth_type, len;
	u8	bsnaphdr;
	u8	*psnap_type;
	struct ieee80211_snap_hdr	*psnap;
	
	sint ret=_SUCCESS;
	_adapter			*adapter =precvframe->u.hdr.adapter;
	struct mlme_priv	*pmlmepriv = &adapter->mlmepriv;

	u8	*ptr = get_recvframe_data(precvframe) ; // point to frame_ctrl field
	struct rx_pkt_attrib *pattrib = & precvframe->u.hdr.attrib;

_func_enter_;

	if(pattrib->encrypt){
		recvframe_pull_tail(precvframe, pattrib->icv_len);	
	}

	psnap=(struct ieee80211_snap_hdr	*)(ptr+pattrib->hdrlen + pattrib->iv_len);
	psnap_type=ptr+pattrib->hdrlen + pattrib->iv_len+SNAP_SIZE;
	/* convert hdr + possible LLC headers into Ethernet header */
	//eth_type = (psnap_type[0] << 8) | psnap_type[1];
	if((_rtw_memcmp(psnap, rtw_rfc1042_header, SNAP_SIZE) &&
		(_rtw_memcmp(psnap_type, SNAP_ETH_TYPE_IPX, 2) == _FALSE) && 
		(_rtw_memcmp(psnap_type, SNAP_ETH_TYPE_APPLETALK_AARP, 2)==_FALSE) )||
		//eth_type != ETH_P_AARP && eth_type != ETH_P_IPX) ||
		 _rtw_memcmp(psnap, rtw_bridge_tunnel_header, SNAP_SIZE)){
		/* remove RFC1042 or Bridge-Tunnel encapsulation and replace EtherType */
		bsnaphdr = _TRUE;
	}
	else {
		/* Leave Ethernet header part of hdr and full payload */
		bsnaphdr = _FALSE;
	}

	rmv_len = pattrib->hdrlen + pattrib->iv_len +(bsnaphdr?SNAP_SIZE:0);
	len = precvframe->u.hdr.len - rmv_len;

	RT_TRACE(_module_rtl871x_recv_c_,_drv_info_,("\n===pattrib->hdrlen: %x,  pattrib->iv_len:%x ===\n\n", pattrib->hdrlen,  pattrib->iv_len));

	_rtw_memcpy(&eth_type, ptr+rmv_len, 2);
	eth_type= ntohs((unsigned short )eth_type); //pattrib->ether_type
	pattrib->eth_type = eth_type;

	if ((check_fwstate(pmlmepriv, WIFI_MP_STATE) == _TRUE))	   	
	{
		ptr += rmv_len ;	
		*ptr = 0x87;
		*(ptr+1) = 0x12;

		eth_type = 0x8712;
		// append rx status for mp test packets
		ptr = recvframe_pull(precvframe, (rmv_len-sizeof(struct ethhdr)+2)-24);
		_rtw_memcpy(ptr, get_rxmem(precvframe), 24);
		ptr+=24;
	}
	else {
		ptr = recvframe_pull(precvframe, (rmv_len-sizeof(struct ethhdr)+ (bsnaphdr?2:0)));
	}

	_rtw_memcpy(ptr, pattrib->dst, ETH_ALEN);
	_rtw_memcpy(ptr+ETH_ALEN, pattrib->src, ETH_ALEN);

	if(!bsnaphdr) {
		len = htons(len);
		_rtw_memcpy(ptr+12, &len, 2);
	}

_func_exit_;	
	return ret;

}