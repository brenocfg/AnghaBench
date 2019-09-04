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
typedef  scalar_t__ u8 ;
struct xmit_priv {int dummy; } ;
struct pkt_attrib {int retry_ctrl; size_t pktlen; size_t last_txcmdsz; int /*<<< orphan*/  seqnum; } ;
struct xmit_frame {scalar_t__ buf_addr; struct pkt_attrib attrib; } ;
struct mlme_ext_priv {int /*<<< orphan*/  mgnt_seq; scalar_t__ cur_channel; } ;
struct ieee80211_hdr {int dummy; } ;
struct adapter {int /*<<< orphan*/  mlmepriv; struct mlme_ext_priv mlmeextpriv; struct xmit_priv xmitpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_WIDTH_20 ; 
 int /*<<< orphan*/  GetSequence (struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 int TXDESC_OFFSET ; 
 int WLANHDR_OFFSET ; 
 int _FAIL ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int _SUCCESS ; 
 struct xmit_frame* alloc_mgtxmitframe (struct xmit_priv*) ; 
 int /*<<< orphan*/  check_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dump_mgntframe_and_wait_ack (struct adapter*,struct xmit_frame*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void*,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ rtw_get_oper_ch (struct adapter*) ; 
 int /*<<< orphan*/  rtw_scan_abort (struct adapter*) ; 
 int /*<<< orphan*/  rtw_set_scan_deny (struct adapter*,int) ; 
 int /*<<< orphan*/  set_channel_bwmode (struct adapter*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_mgntframe_attrib (struct adapter*,struct pkt_attrib*) ; 

__attribute__((used)) static int _cfg80211_rtw_mgmt_tx(struct adapter *padapter, u8 tx_ch, const u8 *buf, size_t len)
{
	struct xmit_frame	*pmgntframe;
	struct pkt_attrib	*pattrib;
	unsigned char *pframe;
	int ret = _FAIL;
	bool ack = true;
	struct ieee80211_hdr *pwlanhdr;
	struct xmit_priv *pxmitpriv = &(padapter->xmitpriv);
	struct mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);

	rtw_set_scan_deny(padapter, 1000);

	rtw_scan_abort(padapter);
	if (tx_ch != rtw_get_oper_ch(padapter)) {
		if (!check_fwstate(&padapter->mlmepriv, _FW_LINKED))
			pmlmeext->cur_channel = tx_ch;
		set_channel_bwmode(padapter, tx_ch, HAL_PRIME_CHNL_OFFSET_DONT_CARE, CHANNEL_WIDTH_20);
	}

	/* starting alloc mgmt frame to dump it */
	if ((pmgntframe = alloc_mgtxmitframe(pxmitpriv)) == NULL)
	{
		/* ret = -ENOMEM; */
		ret = _FAIL;
		goto exit;
	}

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);
	pattrib->retry_ctrl = false;

	memset(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;

	memcpy(pframe, (void*)buf, len);
	pattrib->pktlen = len;

	pwlanhdr = (struct ieee80211_hdr *)pframe;
	/* update seq number */
	pmlmeext->mgnt_seq = GetSequence(pwlanhdr);
	pattrib->seqnum = pmlmeext->mgnt_seq;
	pmlmeext->mgnt_seq++;

	pattrib->last_txcmdsz = pattrib->pktlen;

	if (dump_mgntframe_and_wait_ack(padapter, pmgntframe) != _SUCCESS)
	{
		ack = false;
		ret = _FAIL;

		#ifdef DEBUG_CFG80211
		DBG_8192C("%s, ack == _FAIL\n", __func__);
		#endif
	}
	else
	{

		msleep(50);

		#ifdef DEBUG_CFG80211
		DBG_8192C("%s, ack =%d, ok!\n", __func__, ack);
		#endif
		ret = _SUCCESS;
	}

exit:

	#ifdef DEBUG_CFG80211
	DBG_8192C("%s, ret =%d\n", __func__, ret);
	#endif

	return ret;

}