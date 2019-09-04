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
struct dvobj_priv {scalar_t__ oper_channel; int /*<<< orphan*/  on_oper_ch_time; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 int /*<<< orphan*/  jiffies ; 

inline void rtw_set_oper_ch(struct adapter *adapter, u8 ch)
{
#ifdef DBG_CH_SWITCH
	const int len = 128;
	char msg[128] = {0};
	int cnt = 0;
	int i = 0;
#endif  /* DBG_CH_SWITCH */
	struct dvobj_priv *dvobj = adapter_to_dvobj(adapter);

	if (dvobj->oper_channel != ch) {
		dvobj->on_oper_ch_time = jiffies;

#ifdef DBG_CH_SWITCH
		cnt += snprintf(msg+cnt, len-cnt, "switch to ch %3u", ch);

		for (i = 0; i < dvobj->iface_nums; i++) {
			struct adapter *iface = dvobj->padapters[i];
			cnt += snprintf(msg+cnt, len-cnt, " ["ADPT_FMT":", ADPT_ARG(iface));
			if (iface->mlmeextpriv.cur_channel == ch)
				cnt += snprintf(msg+cnt, len-cnt, "C");
			else
				cnt += snprintf(msg+cnt, len-cnt, "_");
			if (iface->wdinfo.listen_channel == ch && !rtw_p2p_chk_state(&iface->wdinfo, P2P_STATE_NONE))
				cnt += snprintf(msg+cnt, len-cnt, "L");
			else
				cnt += snprintf(msg+cnt, len-cnt, "_");
			cnt += snprintf(msg+cnt, len-cnt, "]");
		}

		DBG_871X(FUNC_ADPT_FMT" %s\n", FUNC_ADPT_ARG(adapter), msg);
#endif /* DBG_CH_SWITCH */
	}

	dvobj->oper_channel = ch;
}