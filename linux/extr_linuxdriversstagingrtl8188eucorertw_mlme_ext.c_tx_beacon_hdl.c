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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*) ; 
 int /*<<< orphan*/  H2C_PARAMETERS_ERROR ; 
 int /*<<< orphan*/  H2C_SUCCESS ; 
 scalar_t__ _FAIL ; 
 scalar_t__ send_beacon (struct adapter*) ; 

u8 tx_beacon_hdl(struct adapter *padapter, unsigned char *pbuf)
{
	if (send_beacon(padapter) == _FAIL) {
		DBG_88E("issue_beacon, fail!\n");
		return H2C_PARAMETERS_ERROR;
	}
#ifdef CONFIG_88EU_AP_MODE
	else { /* tx bc/mc frames after update TIM */
		struct sta_info *psta_bmc;
		struct list_head *xmitframe_plist, *xmitframe_phead;
		struct xmit_frame *pxmitframe = NULL;
		struct sta_priv  *pstapriv = &padapter->stapriv;

		/* for BC/MC Frames */
		psta_bmc = rtw_get_bcmc_stainfo(padapter);
		if (!psta_bmc)
			return H2C_SUCCESS;

		if ((pstapriv->tim_bitmap&BIT(0)) && (psta_bmc->sleepq_len > 0)) {
			msleep(10);/*  10ms, ATIM(HIQ) Windows */
			spin_lock_bh(&psta_bmc->sleep_q.lock);

			xmitframe_phead = get_list_head(&psta_bmc->sleep_q);
			xmitframe_plist = xmitframe_phead->next;

			while (xmitframe_phead != xmitframe_plist) {
				pxmitframe = container_of(xmitframe_plist, struct xmit_frame, list);

				xmitframe_plist = xmitframe_plist->next;

				list_del_init(&pxmitframe->list);

				psta_bmc->sleepq_len--;
				if (psta_bmc->sleepq_len > 0)
					pxmitframe->attrib.mdata = 1;
				else
					pxmitframe->attrib.mdata = 0;

				pxmitframe->attrib.triggered = 1;

				pxmitframe->attrib.qsel = 0x11;/* HIQ */

				spin_unlock_bh(&psta_bmc->sleep_q.lock);
				if (rtw_hal_xmit(padapter, pxmitframe))
					rtw_os_xmit_complete(padapter, pxmitframe);
				spin_lock_bh(&psta_bmc->sleep_q.lock);
			}
			spin_unlock_bh(&psta_bmc->sleep_q.lock);
		}
	}
#endif
	return H2C_SUCCESS;
}