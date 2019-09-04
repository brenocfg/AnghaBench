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
struct recv_frame {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int _FAIL ; 

__attribute__((used)) static int validate_recv_ctrl_frame(struct adapter *padapter,
				    struct recv_frame *precv_frame)
{
#ifdef CONFIG_88EU_AP_MODE
	struct rx_pkt_attrib *pattrib = &precv_frame->attrib;
	struct sta_priv *pstapriv = &padapter->stapriv;
	u8 *pframe = precv_frame->pkt->data;

	if (GetFrameType(pframe) != WIFI_CTRL_TYPE)
		return _FAIL;

	/* receive the frames that ra(a1) is my address */
	if (memcmp(GetAddr1Ptr(pframe), myid(&padapter->eeprompriv), ETH_ALEN))
		return _FAIL;

	/* only handle ps-poll */
	if (GetFrameSubType(pframe) == WIFI_PSPOLL) {
		u16 aid;
		u8 wmmps_ac = 0;
		struct sta_info *psta = NULL;

		aid = GetAid(pframe);
		psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));

		if ((psta == NULL) || (psta->aid != aid))
			return _FAIL;

		/* for rx pkt statistics */
		psta->sta_stats.rx_ctrl_pkts++;

		switch (pattrib->priority) {
		case 1:
		case 2:
			wmmps_ac = psta->uapsd_bk&BIT(0);
			break;
		case 4:
		case 5:
			wmmps_ac = psta->uapsd_vi&BIT(0);
			break;
		case 6:
		case 7:
			wmmps_ac = psta->uapsd_vo&BIT(0);
			break;
		case 0:
		case 3:
		default:
			wmmps_ac = psta->uapsd_be&BIT(0);
			break;
		}

		if (wmmps_ac)
			return _FAIL;

		if (psta->state & WIFI_STA_ALIVE_CHK_STATE) {
			DBG_88E("%s alive check-rx ps-poll\n", __func__);
			psta->expire_to = pstapriv->expire_to;
			psta->state ^= WIFI_STA_ALIVE_CHK_STATE;
		}

		if ((psta->state&WIFI_SLEEP_STATE) && (pstapriv->sta_dz_bitmap&BIT(psta->aid))) {
			struct list_head *xmitframe_plist, *xmitframe_phead;
			struct xmit_frame *pxmitframe = NULL;

			spin_lock_bh(&psta->sleep_q.lock);

			xmitframe_phead = get_list_head(&psta->sleep_q);
			xmitframe_plist = xmitframe_phead->next;

			if (xmitframe_phead != xmitframe_plist) {
				pxmitframe = list_entry(xmitframe_plist, struct xmit_frame, list);

				xmitframe_plist = xmitframe_plist->next;

				list_del_init(&pxmitframe->list);

				psta->sleepq_len--;

				if (psta->sleepq_len > 0)
					pxmitframe->attrib.mdata = 1;
				else
					pxmitframe->attrib.mdata = 0;

				pxmitframe->attrib.triggered = 1;

				spin_unlock_bh(&psta->sleep_q.lock);
				if (rtw_hal_xmit(padapter, pxmitframe) == true)
					rtw_os_xmit_complete(padapter, pxmitframe);
				spin_lock_bh(&psta->sleep_q.lock);

				if (psta->sleepq_len == 0) {
					pstapriv->tim_bitmap &= ~BIT(psta->aid);

					/* update BCN for TIM IE */
					/* update_BCNTIM(padapter); */
					update_beacon(padapter, _TIM_IE_, NULL, false);
				}
			} else {
				if (pstapriv->tim_bitmap&BIT(psta->aid)) {
					if (psta->sleepq_len == 0) {
						DBG_88E("no buffered packets to xmit\n");

						/* issue nulldata with More data bit = 0 to indicate we have no buffered packets */
						issue_nulldata(padapter, psta->hwaddr, 0, 0, 0);
					} else {
						DBG_88E("error!psta->sleepq_len=%d\n", psta->sleepq_len);
						psta->sleepq_len = 0;
					}

					pstapriv->tim_bitmap &= ~BIT(psta->aid);

					/* update BCN for TIM IE */
					/* update_BCNTIM(padapter); */
					update_beacon(padapter, _TIM_IE_, NULL, false);
				}
			}

			spin_unlock_bh(&psta->sleep_q.lock);
		}
	}

#endif

	return _FAIL;
}