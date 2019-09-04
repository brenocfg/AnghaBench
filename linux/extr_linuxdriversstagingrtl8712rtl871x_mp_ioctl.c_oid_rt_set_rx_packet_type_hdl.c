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
typedef  int /*<<< orphan*/  uint ;
typedef  int u8 ;
typedef  int u32 ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; scalar_t__ information_buf; scalar_t__ adapter_context; } ;
struct TYPE_2__ {int check_mp_pkt; } ;
struct _adapter {TYPE_1__ mppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCR ; 
 int RCR_AAP ; 
 int RCR_AB ; 
 int RCR_ACRC32 ; 
 int RCR_AM ; 
 int RCR_APM ; 
 int RCR_CBSSID ; 
 int /*<<< orphan*/  RNDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  RNDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 
#define  RX_PKT_BROADCAST 130 
#define  RX_PKT_DEST_ADDR 129 
#define  RX_PKT_PHY_MATCH 128 
 scalar_t__ SET_OID ; 
 int r8712_read32 (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_write32 (struct _adapter*,int /*<<< orphan*/ ,int) ; 

uint oid_rt_set_rx_packet_type_hdl(struct oid_par_priv
					   *poid_par_priv)
{
	struct _adapter *Adapter = (struct _adapter *)
				   (poid_par_priv->adapter_context);
	u8		rx_pkt_type;
	u32		rcr_val32;

	if (poid_par_priv->type_of_oid != SET_OID)
		return RNDIS_STATUS_NOT_ACCEPTED;
	if (poid_par_priv->information_buf_len < sizeof(u8))
		return RNDIS_STATUS_INVALID_LENGTH;
	rx_pkt_type = *((u8 *)poid_par_priv->information_buf);/*4*/
	rcr_val32 = r8712_read32(Adapter, RCR);/*RCR = 0x10250048*/
	rcr_val32 &= ~(RCR_CBSSID | RCR_AB | RCR_AM | RCR_APM | RCR_AAP);
	switch (rx_pkt_type) {
	case RX_PKT_BROADCAST:
		rcr_val32 |= (RCR_AB | RCR_AM | RCR_APM | RCR_AAP | RCR_ACRC32);
		break;
	case RX_PKT_DEST_ADDR:
		rcr_val32 |= (RCR_AB | RCR_AM | RCR_APM | RCR_AAP | RCR_ACRC32);
		break;
	case RX_PKT_PHY_MATCH:
		rcr_val32 |= (RCR_APM | RCR_ACRC32);
		break;
	default:
		rcr_val32 &= ~(RCR_AAP |
			       RCR_APM |
			       RCR_AM |
			       RCR_AB |
			       RCR_ACRC32);
		break;
	}
	if (rx_pkt_type == RX_PKT_DEST_ADDR)
		Adapter->mppriv.check_mp_pkt = 1;
	else
		Adapter->mppriv.check_mp_pkt = 0;
	r8712_write32(Adapter, RCR, rcr_val32);
	return RNDIS_STATUS_SUCCESS;
}