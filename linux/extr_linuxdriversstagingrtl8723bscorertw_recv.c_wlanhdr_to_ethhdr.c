#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int hdrlen; int iv_len; int eth_type; int* dst; int* src; int /*<<< orphan*/  icv_len; scalar_t__ encrypt; } ;
struct TYPE_3__ {int len; struct rx_pkt_attrib attrib; struct adapter* adapter; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int u8 ;
typedef  int u16 ;
struct mlme_priv {int dummy; } ;
typedef  int ieee80211_snap_hdr ;
struct ethhdr {int dummy; } ;
struct adapter {struct mlme_priv mlmepriv; } ;
typedef  int sint ;
typedef  int __be16 ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SNAP_ETH_TYPE_APPLETALK_AARP ; 
 int /*<<< orphan*/  SNAP_ETH_TYPE_IPX ; 
 int SNAP_SIZE ; 
 int /*<<< orphan*/  WIFI_MP_STATE ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int* get_recvframe_data (union recv_frame*) ; 
 int* get_rxmem (union recv_frame*) ; 
 int htons (int) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int ntohs (int) ; 
 int* recvframe_pull (union recv_frame*,int) ; 
 int /*<<< orphan*/  recvframe_pull_tail (union recv_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_bridge_tunnel_header ; 
 int /*<<< orphan*/  rtw_rfc1042_header ; 

sint wlanhdr_to_ethhdr(union recv_frame *precvframe)
{
	sint	rmv_len;
	u16 eth_type, len;
	u8 bsnaphdr;
	u8 *psnap_type;
	struct ieee80211_snap_hdr	*psnap;
	__be16 be_tmp;
	sint ret = _SUCCESS;
	struct adapter			*adapter = precvframe->u.hdr.adapter;
	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;
	u8 *ptr = get_recvframe_data(precvframe) ; /*  point to frame_ctrl field */
	struct rx_pkt_attrib *pattrib = &precvframe->u.hdr.attrib;

	if (pattrib->encrypt) {
		recvframe_pull_tail(precvframe, pattrib->icv_len);
	}

	psnap = (struct ieee80211_snap_hdr	*)(ptr+pattrib->hdrlen + pattrib->iv_len);
	psnap_type = ptr+pattrib->hdrlen + pattrib->iv_len+SNAP_SIZE;
	/* convert hdr + possible LLC headers into Ethernet header */
	/* eth_type = (psnap_type[0] << 8) | psnap_type[1]; */
	if ((!memcmp(psnap, rtw_rfc1042_header, SNAP_SIZE) &&
		(memcmp(psnap_type, SNAP_ETH_TYPE_IPX, 2)) &&
		(memcmp(psnap_type, SNAP_ETH_TYPE_APPLETALK_AARP, 2))) ||
		/* eth_type != ETH_P_AARP && eth_type != ETH_P_IPX) || */
		 !memcmp(psnap, rtw_bridge_tunnel_header, SNAP_SIZE)) {
		/* remove RFC1042 or Bridge-Tunnel encapsulation and replace EtherType */
		bsnaphdr = true;
	} else
		/* Leave Ethernet header part of hdr and full payload */
		bsnaphdr = false;

	rmv_len = pattrib->hdrlen + pattrib->iv_len + (bsnaphdr?SNAP_SIZE:0);
	len = precvframe->u.hdr.len - rmv_len;

	RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("\n ===pattrib->hdrlen: %x,  pattrib->iv_len:%x ===\n\n", pattrib->hdrlen,  pattrib->iv_len));

	memcpy(&be_tmp, ptr+rmv_len, 2);
	eth_type = ntohs(be_tmp); /* pattrib->ether_type */
	pattrib->eth_type = eth_type;

#ifdef CONFIG_AUTO_AP_MODE
	if (0x8899 == pattrib->eth_type) {
		struct sta_info *psta = precvframe->u.hdr.psta;

		DBG_871X("wlan rx: got eth_type = 0x%x\n", pattrib->eth_type);

		if (psta && psta->isrc && psta->pid > 0) {
			u16 rx_pid;

			rx_pid = *(u16 *)(ptr+rmv_len+2);

			DBG_871X("wlan rx(pid = 0x%x): sta("MAC_FMT") pid = 0x%x\n",
				rx_pid, MAC_ARG(psta->hwaddr), psta->pid);

			if (rx_pid == psta->pid) {
				int i;
				u16 len = *(u16 *)(ptr+rmv_len+4);
				/* u16 ctrl_type = *(u16*)(ptr+rmv_len+6); */

				/* DBG_871X("RC: len = 0x%x, ctrl_type = 0x%x\n", len, ctrl_type); */
				DBG_871X("RC: len = 0x%x\n", len);

				for (i = 0; i < len ; i++)
					DBG_871X("0x%x\n", *(ptr+rmv_len+6+i));
					/* DBG_871X("0x%x\n", *(ptr+rmv_len+8+i)); */

				DBG_871X("RC-end\n");
			}
		}
	}
#endif /* CONFIG_AUTO_AP_MODE */

	if ((check_fwstate(pmlmepriv, WIFI_MP_STATE) == true)) {
		ptr += rmv_len;
		*ptr = 0x87;
		*(ptr+1) = 0x12;

		eth_type = 0x8712;
		/*  append rx status for mp test packets */
		ptr = recvframe_pull(precvframe, (rmv_len-sizeof(struct ethhdr)+2)-24);
		memcpy(ptr, get_rxmem(precvframe), 24);
		ptr += 24;
	} else
		ptr = recvframe_pull(precvframe, (rmv_len-sizeof(struct ethhdr) + (bsnaphdr?2:0)));

	memcpy(ptr, pattrib->dst, ETH_ALEN);
	memcpy(ptr+ETH_ALEN, pattrib->src, ETH_ALEN);

	if (!bsnaphdr) {
		be_tmp = htons(len);
		memcpy(ptr+12, &be_tmp, 2);
	}

	return ret;
}