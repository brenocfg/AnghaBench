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

__attribute__((used)) static void process_pwrbit_data(struct adapter *padapter,
				struct recv_frame *precv_frame)
{
#ifdef CONFIG_88EU_AP_MODE
	unsigned char pwrbit;
	u8 *ptr = precv_frame->pkt->data;
	struct rx_pkt_attrib *pattrib = &precv_frame->attrib;
	struct sta_priv *pstapriv = &padapter->stapriv;
	struct sta_info *psta = NULL;

	psta = rtw_get_stainfo(pstapriv, pattrib->src);

	pwrbit = GetPwrMgt(ptr);

	if (psta) {
		if (pwrbit) {
			if (!(psta->state & WIFI_SLEEP_STATE))
				stop_sta_xmit(padapter, psta);
		} else {
			if (psta->state & WIFI_SLEEP_STATE)
				wakeup_sta_to_xmit(padapter, psta);
		}
	}

#endif
}