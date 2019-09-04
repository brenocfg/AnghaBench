#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  scalar_t__ u8 ;
struct pkt_attrib {int mac_id; int qsel; int raid; scalar_t__ ampdu_en; int seqnum; int ether_type; int dhcp_pkt; scalar_t__ retry_ctrl; scalar_t__ qos_en; scalar_t__ ht_en; int /*<<< orphan*/  ra; } ;
struct xmit_frame {int pkt_offset; int frame_tag; struct pkt_attrib attrib; TYPE_1__* padapter; } ;
struct tx_desc {int /*<<< orphan*/  txdw1; int /*<<< orphan*/  txdw0; int /*<<< orphan*/  txdw3; int /*<<< orphan*/  txdw4; int /*<<< orphan*/  txdw5; } ;
struct ht_priv {int dummy; } ;
struct mlme_priv {struct ht_priv htpriv; } ;
struct mlme_ext_info {scalar_t__ preamble_mode; } ;
struct mlme_ext_priv {int /*<<< orphan*/  tx_rate; struct mlme_ext_info mlmext_info; } ;
struct dm_priv {int* INIDATA_RATE; } ;
typedef  scalar_t__ sint ;
typedef  int s32 ;
struct TYPE_6__ {struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_7__ {struct dm_priv dmpriv; } ;
typedef  TYPE_2__ HAL_DATA_TYPE ;

/* Variables and functions */
 int BIT (int) ; 
 int DATA_FRAMETAG ; 
 int /*<<< orphan*/  DBG_8192C (char*,...) ; 
 int FSG ; 
 TYPE_2__* GET_HAL_DATA (TYPE_1__*) ; 
 scalar_t__ IS_MCAST (int /*<<< orphan*/ ) ; 
 int LSG ; 
 int MGNT_FRAMETAG ; 
 int MRateToHwRate (int /*<<< orphan*/ ) ; 
 int OFFSET_SHT ; 
 int OFFSET_SZ ; 
 int OWN ; 
 int PACKET_OFFSET_SZ ; 
 scalar_t__ PREAMBLE_SHORT ; 
 int QSEL_SHT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int TXAGG_FRAMETAG ; 
 int TXDESC_SIZE ; 
 scalar_t__ _FALSE ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_xmit_c_ ; 
 int /*<<< orphan*/  _rtw_memset (struct tx_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  fill_txdesc_phy (struct pkt_attrib*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_txdesc_sectype (struct pkt_attrib*,struct tx_desc*) ; 
 int /*<<< orphan*/  fill_txdesc_vcs (struct pkt_attrib*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl8192cu_cal_txdesc_chksum (struct tx_desc*) ; 
 scalar_t__ urb_zero_packet_chk (TYPE_1__*,int) ; 

__attribute__((used)) static s32 update_txdesc(struct xmit_frame *pxmitframe, u8 *pmem, s32 sz, u8 bagg_pkt)
{
	int	pull=0;
	uint	qsel;
	_adapter			*padapter = pxmitframe->padapter;
	struct mlme_priv	*pmlmepriv = &padapter->mlmepriv;		
	struct pkt_attrib	*pattrib = &pxmitframe->attrib;
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	struct dm_priv	*pdmpriv = &pHalData->dmpriv;
	struct tx_desc	*ptxdesc = (struct tx_desc *)pmem;
	struct ht_priv		*phtpriv = &pmlmepriv->htpriv;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	sint	bmcst = IS_MCAST(pattrib->ra);
#ifdef CONFIG_P2P
	struct wifidirect_info*	pwdinfo = &padapter->wdinfo;
#endif //CONFIG_P2P

#ifndef CONFIG_USE_USB_BUFFER_ALLOC_TX
	if((_FALSE == bagg_pkt) && (urb_zero_packet_chk(padapter, sz)==0))
	{
		ptxdesc = (struct tx_desc *)(pmem+PACKET_OFFSET_SZ);
		pull = 1;
		pxmitframe->pkt_offset --;
	}
#endif	// CONFIG_USE_USB_BUFFER_ALLOC_TX

	_rtw_memset(ptxdesc, 0, sizeof(struct tx_desc));

	if((pxmitframe->frame_tag&0x0f) == DATA_FRAMETAG)
	{
		//DBG_8192C("pxmitframe->frame_tag == DATA_FRAMETAG\n");			

		//offset 4
		ptxdesc->txdw1 |= cpu_to_le32(pattrib->mac_id&0x1f);

		qsel = (uint)(pattrib->qsel & 0x0000001f);
		ptxdesc->txdw1 |= cpu_to_le32((qsel << QSEL_SHT) & 0x00001f00);

		ptxdesc->txdw1 |= cpu_to_le32((pattrib->raid<< 16) & 0x000f0000);

		fill_txdesc_sectype(pattrib, ptxdesc);

		if(pattrib->ampdu_en==_TRUE)
			ptxdesc->txdw1 |= cpu_to_le32(BIT(5));//AGG EN
		else
			ptxdesc->txdw1 |= cpu_to_le32(BIT(6));//AGG BK
		
		//offset 8


		//offset 12
		ptxdesc->txdw3 |= cpu_to_le32((pattrib->seqnum<<16)&0xffff0000);


		//offset 16 , offset 20
		if (pattrib->qos_en)
			ptxdesc->txdw4 |= cpu_to_le32(BIT(6));//QoS

		if ((pattrib->ether_type != 0x888e) && (pattrib->ether_type != 0x0806) && (pattrib->dhcp_pkt != 1))
		{
              	//Non EAP & ARP & DHCP type data packet
              	
			fill_txdesc_vcs(pattrib, &ptxdesc->txdw4);
			fill_txdesc_phy(pattrib, &ptxdesc->txdw4);

			ptxdesc->txdw4 |= cpu_to_le32(0x00000008);//RTS Rate=24M
			ptxdesc->txdw5 |= cpu_to_le32(0x0001ff00);//
			//ptxdesc->txdw5 |= cpu_to_le32(0x0000000b);//DataRate - 54M

			//use REG_INIDATA_RATE_SEL value
			ptxdesc->txdw5 |= cpu_to_le32(pdmpriv->INIDATA_RATE[pattrib->mac_id]);

              	if(0)//for driver dbg
			{
				ptxdesc->txdw4 |= cpu_to_le32(BIT(8));//driver uses rate
				
				if(pattrib->ht_en)
					ptxdesc->txdw5 |= cpu_to_le32(BIT(6));//SGI

				ptxdesc->txdw5 |= cpu_to_le32(0x00000013);//init rate - mcs7
			}

		}
		else
		{
			// EAP data packet and ARP packet.
			// Use the 1M data rate to send the EAP/ARP packet.
			// This will maybe make the handshake smooth.

			ptxdesc->txdw1 |= cpu_to_le32(BIT(6));//AGG BK
			
		   	ptxdesc->txdw4 |= cpu_to_le32(BIT(8));//driver uses rate

			if (pmlmeinfo->preamble_mode == PREAMBLE_SHORT)
				ptxdesc->txdw4 |= cpu_to_le32(BIT(24));// DATA_SHORT

			ptxdesc->txdw5 |= cpu_to_le32(MRateToHwRate(pmlmeext->tx_rate));
		}
		
		//offset 24
#ifdef CONFIG_TCP_CSUM_OFFLOAD_TX
		if ( pattrib->hw_tcp_csum == 1 ) {
			// ptxdesc->txdw6 = 0; // clear TCP_CHECKSUM and IP_CHECKSUM. It's zero already!!
			u8 ip_hdr_offset = 32 + pattrib->hdrlen + pattrib->iv_len + 8;
			ptxdesc->txdw7 = (1 << 31) | (ip_hdr_offset << 16);
			DBG_8192C("ptxdesc->txdw7 = %08x\n", ptxdesc->txdw7);
		}
#endif
	}
	else if((pxmitframe->frame_tag&0x0f)== MGNT_FRAMETAG)
	{
		//DBG_8192C("pxmitframe->frame_tag == MGNT_FRAMETAG\n");	
		
		//offset 4		
		ptxdesc->txdw1 |= cpu_to_le32(pattrib->mac_id&0x1f);
		
		qsel = (uint)(pattrib->qsel&0x0000001f);
		ptxdesc->txdw1 |= cpu_to_le32((qsel<<QSEL_SHT)&0x00001f00);

		ptxdesc->txdw1 |= cpu_to_le32((pattrib->raid<< 16) & 0x000f0000);
		
		//fill_txdesc_sectype(pattrib, ptxdesc);
		
		//offset 8		
#ifdef CONFIG_XMIT_ACK
		//CCX-TXRPT ack for xmit mgmt frames.
		if (pxmitframe->ack_report) {
			ptxdesc->txdw2 |= cpu_to_le32(BIT(19));
			#ifdef DBG_CCX
			DBG_871X("%s set ccx\n", __func__);
			#endif
		}
#endif //CONFIG_XMIT_ACK

		//offset 12
		ptxdesc->txdw3 |= cpu_to_le32((pattrib->seqnum<<16)&0xffff0000);
		
		//offset 16
		ptxdesc->txdw4 |= cpu_to_le32(BIT(8));//driver uses rate
		
		//offset 20
		ptxdesc->txdw5 |= cpu_to_le32(BIT(17));//retry limit enable
		if(pattrib->retry_ctrl == _TRUE)
		{
#ifdef CONFIG_P2P
			if(!rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE))
			{
#ifdef CONFIG_INTEL_WIDI
				if(padapter->mlmepriv.widi_enable == _TRUE)
					ptxdesc->txdw5 |= cpu_to_le32(0x00180000);//retry limit = 6
				else
#endif //CONFIG_INTEL_WIDI
					ptxdesc->txdw5 |= cpu_to_le32(0x00080000);//retry limit = 2
			}
			else
#endif //CONFIG_P2P
				ptxdesc->txdw5 |= cpu_to_le32(0x00180000);//retry limit = 6			
		}
		else
			ptxdesc->txdw5 |= cpu_to_le32(0x00300000);//retry limit = 12

#ifdef CONFIG_INTEL_PROXIM
		if((padapter->proximity.proxim_on==_TRUE)&&(pattrib->intel_proxim==_TRUE)){
			printk("\n %s pattrib->rate=%d\n",__FUNCTION__,pattrib->rate);
			ptxdesc->txdw5 |= cpu_to_le32( pattrib->rate);
		}
		else
#endif
		{
			ptxdesc->txdw5 |= cpu_to_le32(MRateToHwRate(pmlmeext->tx_rate));
		}
	}
	else if((pxmitframe->frame_tag&0x0f) == TXAGG_FRAMETAG)
	{
		DBG_8192C("pxmitframe->frame_tag == TXAGG_FRAMETAG\n");
	}
#ifdef CONFIG_MP_INCLUDED
	else if((pxmitframe->frame_tag&0x0f) == MP_FRAMETAG)
	{
		fill_txdesc_for_mp(padapter, ptxdesc);
	}
#endif
	else
	{
		DBG_8192C("pxmitframe->frame_tag = %d\n", pxmitframe->frame_tag);
		
		//offset 4	
		ptxdesc->txdw1 |= cpu_to_le32((4)&0x1f);//CAM_ID(MAC_ID)
		
		ptxdesc->txdw1 |= cpu_to_le32((6<< 16) & 0x000f0000);//raid
		
		//offset 8		

		//offset 12
		ptxdesc->txdw3 |= cpu_to_le32((pattrib->seqnum<<16)&0xffff0000);
		
		//offset 16
		ptxdesc->txdw4 |= cpu_to_le32(BIT(8));//driver uses rate
		
		//offset 20
		ptxdesc->txdw5 |= cpu_to_le32(MRateToHwRate(pmlmeext->tx_rate));
	}

	// 2009.11.05. tynli_test. Suggested by SD4 Filen for FW LPS.
	// (1) The sequence number of each non-Qos frame / broadcast / multicast /
	// mgnt frame should be controled by Hw because Fw will also send null data
	// which we cannot control when Fw LPS enable.
	// --> default enable non-Qos data sequense number. 2010.06.23. by tynli.
	// (2) Enable HW SEQ control for beacon packet, because we use Hw beacon.
	// (3) Use HW Qos SEQ to control the seq num of Ext port non-Qos packets.
	// 2010.06.23. Added by tynli.
	if(!pattrib->qos_en)
	{		
		ptxdesc->txdw4 |= cpu_to_le32(BIT(7)); // Hw set sequence number
		ptxdesc->txdw3 |= cpu_to_le32((8 <<28)); //set bit3 to 1. Suugested by TimChen. 2009.12.29.
	}

	//offset 0
	ptxdesc->txdw0 |= cpu_to_le32(sz&0x0000ffff);
	ptxdesc->txdw0 |= cpu_to_le32(OWN | FSG | LSG);
	ptxdesc->txdw0 |= cpu_to_le32(((TXDESC_SIZE+OFFSET_SZ)<<OFFSET_SHT)&0x00ff0000);//32 bytes for TX Desc

	if(bmcst)	
	{
		ptxdesc->txdw0 |= cpu_to_le32(BIT(24));
	}	

	RT_TRACE(_module_rtl871x_xmit_c_,_drv_info_,("offset0-txdesc=0x%x\n", ptxdesc->txdw0));

	//offset 4
	// pkt_offset, unit:8 bytes padding
	if (pxmitframe->pkt_offset > 0)
		ptxdesc->txdw1 |= cpu_to_le32((pxmitframe->pkt_offset << 26) & 0x7c000000);

#ifdef CONFIG_USB_TX_AGGREGATION
	if (pxmitframe->agg_num > 1)
		ptxdesc->txdw5 |= cpu_to_le32((pxmitframe->agg_num << 24) & 0xff000000);
#endif

	rtl8192cu_cal_txdesc_chksum(ptxdesc);
		
	return pull;
		
}