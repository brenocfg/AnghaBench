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
typedef  int u8 ;
typedef  int u16 ;
struct wlan_bssid_ex {int dummy; } ;
struct evt_priv {int event_seq; int /*<<< orphan*/  evt_done_cnt; } ;
struct _adapter {struct evt_priv evtpriv; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int parmsize; void (* event_callback ) (struct _adapter*,int*) ;} ;

/* Variables and functions */
 int GEN_EVT_CODE (int /*<<< orphan*/ ) ; 
 int MAX_C2HEVT ; 
 int /*<<< orphan*/  _Survey ; 
 int /*<<< orphan*/  _WPS_PBC ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__* wlanevents ; 

void r8712_event_handle(struct _adapter *padapter, __le32 *peventbuf)
{
	u8 evt_code, evt_seq;
	u16 evt_sz;
	void (*event_callback)(struct _adapter *dev, u8 *pbuf);
	struct	evt_priv *pevt_priv = &padapter->evtpriv;

	if (!peventbuf)
		goto _abort_event_;
	evt_sz = (u16)(le32_to_cpu(*peventbuf) & 0xffff);
	evt_seq = (u8)((le32_to_cpu(*peventbuf) >> 24) & 0x7f);
	evt_code = (u8)((le32_to_cpu(*peventbuf) >> 16) & 0xff);
	/* checking event sequence... */
	if ((evt_seq & 0x7f) != pevt_priv->event_seq) {
		pevt_priv->event_seq = ((evt_seq + 1) & 0x7f);
		goto _abort_event_;
	}
	/* checking if event code is valid */
	if (evt_code >= MAX_C2HEVT) {
		pevt_priv->event_seq = ((evt_seq + 1) & 0x7f);
		goto _abort_event_;
	} else if ((evt_code == GEN_EVT_CODE(_Survey)) &&
		   (evt_sz > sizeof(struct wlan_bssid_ex))) {
		pevt_priv->event_seq = ((evt_seq + 1) & 0x7f);
		goto _abort_event_;
	}
	/* checking if event size match the event parm size */
	if ((wlanevents[evt_code].parmsize) &&
	    (wlanevents[evt_code].parmsize != evt_sz)) {
		pevt_priv->event_seq = ((evt_seq + 1) & 0x7f);
		goto _abort_event_;
	} else if ((evt_sz == 0) && (evt_code != GEN_EVT_CODE(_WPS_PBC))) {
		pevt_priv->event_seq = ((evt_seq + 1) & 0x7f);
		goto _abort_event_;
	}
	pevt_priv->event_seq++;	/* update evt_seq */
	if (pevt_priv->event_seq > 127)
		pevt_priv->event_seq = 0;
	/* move to event content, 8 bytes alignment */
	peventbuf = peventbuf + 2;
	event_callback = wlanevents[evt_code].event_callback;
	if (event_callback)
		event_callback(padapter, (u8 *)peventbuf);
	pevt_priv->evt_done_cnt++;
_abort_event_:
	return;
}