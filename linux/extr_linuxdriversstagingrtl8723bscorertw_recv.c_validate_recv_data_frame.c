#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int to_fr_ds; int qos; int priority; int hdrlen; scalar_t__ icv_len; scalar_t__ iv_len; scalar_t__ encrypt; int /*<<< orphan*/ * ra; scalar_t__ privacy; scalar_t__ order; scalar_t__ amsdu; scalar_t__ ack_policy; int /*<<< orphan*/ * ta; int /*<<< orphan*/ * bssid; int /*<<< orphan*/ * src; int /*<<< orphan*/ * dst; } ;
struct TYPE_6__ {int /*<<< orphan*/ * preorder_ctrl; struct sta_info* psta; struct rx_pkt_attrib attrib; int /*<<< orphan*/ * rx_data; } ;
struct TYPE_7__ {TYPE_2__ hdr; } ;
union recv_frame {TYPE_3__ u; } ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {int /*<<< orphan*/  rxcache; } ;
struct sta_info {TYPE_4__ sta_recvpriv; int /*<<< orphan*/ * recvreorder_ctrl; } ;
struct security_priv {int dummy; } ;
struct TYPE_5__ {int bIsAnyNonBEPkts; } ;
struct adapter {TYPE_1__ recvpriv; struct security_priv securitypriv; } ;
typedef  scalar_t__ sint ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GET_ENCRY_ALGO (struct security_priv*,struct sta_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetAMsdu (int /*<<< orphan*/ *) ; 
 scalar_t__ GetAckpolicy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetAddr1Ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetAddr2Ptr (int /*<<< orphan*/ *) ; 
 int GetPriority (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetRetry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_MCAST (int /*<<< orphan*/ *) ; 
 scalar_t__ RTW_RX_HANDLED ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SET_ICE_IV_LEN (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 scalar_t__ ap2sta_data_frame (struct adapter*,union recv_frame*,struct sta_info**) ; 
 int /*<<< orphan*/ * get_da (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_hdr_bssid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_sa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ recv_decache (union recv_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sta2ap_data_frame (struct adapter*,union recv_frame*,struct sta_info**) ; 
 scalar_t__ sta2sta_data_frame (struct adapter*,union recv_frame*,struct sta_info**) ; 

sint validate_recv_data_frame(struct adapter *adapter, union recv_frame *precv_frame)
{
	u8 bretry;
	u8 *psa, *pda, *pbssid;
	struct sta_info *psta = NULL;
	u8 *ptr = precv_frame->u.hdr.rx_data;
	struct rx_pkt_attrib	*pattrib = &precv_frame->u.hdr.attrib;
	struct security_priv *psecuritypriv = &adapter->securitypriv;
	sint ret = _SUCCESS;

	bretry = GetRetry(ptr);
	pda = get_da(ptr);
	psa = get_sa(ptr);
	pbssid = get_hdr_bssid(ptr);

	if (pbssid == NULL) {
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s pbssid == NULL\n", __func__);
		#endif
		ret = _FAIL;
		goto exit;
	}

	memcpy(pattrib->dst, pda, ETH_ALEN);
	memcpy(pattrib->src, psa, ETH_ALEN);

	memcpy(pattrib->bssid, pbssid, ETH_ALEN);

	switch (pattrib->to_fr_ds) {
	case 0:
		memcpy(pattrib->ra, pda, ETH_ALEN);
		memcpy(pattrib->ta, psa, ETH_ALEN);
		ret = sta2sta_data_frame(adapter, precv_frame, &psta);
		break;

	case 1:
		memcpy(pattrib->ra, pda, ETH_ALEN);
		memcpy(pattrib->ta, pbssid, ETH_ALEN);
		ret = ap2sta_data_frame(adapter, precv_frame, &psta);
		break;

	case 2:
		memcpy(pattrib->ra, pbssid, ETH_ALEN);
		memcpy(pattrib->ta, psa, ETH_ALEN);
		ret = sta2ap_data_frame(adapter, precv_frame, &psta);
		break;

	case 3:
		memcpy(pattrib->ra, GetAddr1Ptr(ptr), ETH_ALEN);
		memcpy(pattrib->ta, GetAddr2Ptr(ptr), ETH_ALEN);
		ret = _FAIL;
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, (" case 3\n"));
		break;

	default:
		ret = _FAIL;
		break;

	}

	if (ret == _FAIL) {
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s case:%d, res:%d\n", __func__, pattrib->to_fr_ds, ret);
		#endif
		goto exit;
	} else if (ret == RTW_RX_HANDLED) {
		goto exit;
	}


	if (psta == NULL) {
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, (" after to_fr_ds_chk; psta == NULL\n"));
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s psta == NULL\n", __func__);
		#endif
		ret = _FAIL;
		goto exit;
	}

	/* psta->rssi = prxcmd->rssi; */
	/* psta->signal_quality = prxcmd->sq; */
	precv_frame->u.hdr.psta = psta;


	pattrib->amsdu = 0;
	pattrib->ack_policy = 0;
	/* parsing QC field */
	if (pattrib->qos == 1) {
		pattrib->priority = GetPriority((ptr + 24));
		pattrib->ack_policy = GetAckpolicy((ptr + 24));
		pattrib->amsdu = GetAMsdu((ptr + 24));
		pattrib->hdrlen = pattrib->to_fr_ds == 3 ? 32 : 26;

		if (pattrib->priority != 0 && pattrib->priority != 3)
			adapter->recvpriv.bIsAnyNonBEPkts = true;

	} else{
		pattrib->priority = 0;
		pattrib->hdrlen = pattrib->to_fr_ds == 3 ? 30 : 24;
	}


	if (pattrib->order)/* HT-CTRL 11n */
		pattrib->hdrlen += 4;

	precv_frame->u.hdr.preorder_ctrl = &psta->recvreorder_ctrl[pattrib->priority];

	/*  decache, drop duplicate recv packets */
	if (recv_decache(precv_frame, bretry, &psta->sta_recvpriv.rxcache) == _FAIL) {
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("decache : drop pkt\n"));
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s recv_decache return _FAIL\n", __func__);
		#endif
		ret = _FAIL;
		goto exit;
	}

	if (pattrib->privacy) {

		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("validate_recv_data_frame:pattrib->privacy =%x\n", pattrib->privacy));
		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("\n ^^^^^^^^^^^IS_MCAST(pattrib->ra(0x%02x)) =%d^^^^^^^^^^^^^^^6\n", pattrib->ra[0], IS_MCAST(pattrib->ra)));

		GET_ENCRY_ALGO(psecuritypriv, psta, pattrib->encrypt, IS_MCAST(pattrib->ra));

		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("\n pattrib->encrypt =%d\n", pattrib->encrypt));

		SET_ICE_IV_LEN(pattrib->iv_len, pattrib->icv_len, pattrib->encrypt);
	} else{
		pattrib->encrypt = 0;
		pattrib->iv_len = pattrib->icv_len = 0;
	}

exit:
	return ret;
}