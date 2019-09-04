#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; scalar_t__ information_buf; } ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SET_OID ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_mp_ ; 

NDIS_STATUS oid_rt_set_rx_packet_type_hdl(struct oid_par_priv *poid_par_priv)
{
#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	u8		rx_pkt_type;
//	u32		rcr_val32;
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
//	PADAPTER	padapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	RT_TRACE(_module_mp_, _drv_notice_, ("+oid_rt_set_rx_packet_type_hdl\n"));

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len < sizeof(u8))
		return NDIS_STATUS_INVALID_LENGTH;

	rx_pkt_type = *((u8*)poid_par_priv->information_buf);//4

	RT_TRACE(_module_mp_, _drv_info_, ("rx_pkt_type: %x\n",rx_pkt_type ));
#if 0
	_irqlevel_changed_(&oldirql, LOWER);
#if 0
	rcr_val8 = rtw_read8(Adapter, 0x10250048);//RCR
	rcr_val8 &= ~(RCR_AB|RCR_AM|RCR_APM|RCR_AAP);

	if(rx_pkt_type == RX_PKT_BROADCAST){
		rcr_val8 |= (RCR_AB | RCR_ACRC32 );
	}
	else if(rx_pkt_type == RX_PKT_DEST_ADDR){
		rcr_val8 |= (RCR_AAP| RCR_AM |RCR_ACRC32);
	}
	else if(rx_pkt_type == RX_PKT_PHY_MATCH){
		rcr_val8 |= (RCR_APM|RCR_ACRC32);
	}
	else{
		rcr_val8 &= ~(RCR_AAP|RCR_APM|RCR_AM|RCR_AB|RCR_ACRC32);
	}
	rtw_write8(padapter, 0x10250048,rcr_val8);
#else
	rcr_val32 = rtw_read32(padapter, RCR);//RCR = 0x10250048
	rcr_val32 &= ~(RCR_CBSSID|RCR_AB|RCR_AM|RCR_APM|RCR_AAP);
#if 0
	if(rx_pkt_type == RX_PKT_BROADCAST){
		rcr_val32 |= (RCR_AB|RCR_AM|RCR_APM|RCR_AAP|RCR_ACRC32);
	}
	else if(rx_pkt_type == RX_PKT_DEST_ADDR){
		//rcr_val32 |= (RCR_CBSSID|RCR_AAP|RCR_AM|RCR_ACRC32);
		rcr_val32 |= (RCR_CBSSID|RCR_APM|RCR_ACRC32);
	}
	else if(rx_pkt_type == RX_PKT_PHY_MATCH){
		rcr_val32 |= (RCR_APM|RCR_ACRC32);
		//rcr_val32 |= (RCR_AAP|RCR_ACRC32);
	}
	else{
		rcr_val32 &= ~(RCR_AAP|RCR_APM|RCR_AM|RCR_AB|RCR_ACRC32);
	}
#else
	switch (rx_pkt_type)
	{
		case RX_PKT_BROADCAST :
			rcr_val32 |= (RCR_AB|RCR_AM|RCR_APM|RCR_AAP|RCR_ACRC32);
			break;
		case RX_PKT_DEST_ADDR :
			rcr_val32 |= (RCR_AB|RCR_AM|RCR_APM|RCR_AAP|RCR_ACRC32);
			break;
		case RX_PKT_PHY_MATCH:
			rcr_val32 |= (RCR_APM|RCR_ACRC32);
			break;
		default:
			rcr_val32 &= ~(RCR_AAP|RCR_APM|RCR_AM|RCR_AB|RCR_ACRC32);
			break;
	}

	if (rx_pkt_type == RX_PKT_DEST_ADDR) {
		padapter->mppriv.check_mp_pkt = 1;
	} else {
		padapter->mppriv.check_mp_pkt = 0;
	}
#endif
	rtw_write32(padapter, RCR, rcr_val32);

#endif
	_irqlevel_changed_(&oldirql, RAISE);
#endif
_func_exit_;

	return status;
}