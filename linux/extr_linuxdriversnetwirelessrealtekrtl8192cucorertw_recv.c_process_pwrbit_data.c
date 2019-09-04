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
typedef  union recv_frame {int dummy; } recv_frame ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */

void process_pwrbit_data(_adapter *padapter, union recv_frame *precv_frame)
{
#ifdef CONFIG_AP_MODE
	unsigned char pwrbit;
	u8 *ptr = precv_frame->u.hdr.rx_data;
	struct rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	struct sta_priv *pstapriv = &padapter->stapriv;
	struct sta_info *psta=NULL;

	psta = rtw_get_stainfo(pstapriv, pattrib->src);

	pwrbit = GetPwrMgt(ptr);

	if(psta)
	{
		if(pwrbit)
		{
			if(!(psta->state & WIFI_SLEEP_STATE))
			{
				//psta->state |= WIFI_SLEEP_STATE;
				//pstapriv->sta_dz_bitmap |= BIT(psta->aid);

				stop_sta_xmit(padapter, psta);

				//DBG_871X("to sleep, sta_dz_bitmap=%x\n", pstapriv->sta_dz_bitmap);
			}
		}
		else
		{
			if(psta->state & WIFI_SLEEP_STATE)
			{
				//psta->state ^= WIFI_SLEEP_STATE;
				//pstapriv->sta_dz_bitmap &= ~BIT(psta->aid);				

				wakeup_sta_to_xmit(padapter, psta);

				//DBG_871X("to wakeup, sta_dz_bitmap=%x\n", pstapriv->sta_dz_bitmap);
			}
		}

	}

#endif
}