#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  scalar_t__ u16 ;
struct adapter {int dummy; } ;
struct TYPE_3__ {scalar_t__ CmdLen; void* CmdSeq; void* CmdID; } ;
typedef  TYPE_1__ C2H_EVT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  RT_PRINT_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void**,scalar_t__) ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_hal_init_c_ ; 
 int /*<<< orphan*/  process_c2h_event (struct adapter*,TYPE_1__*,void**) ; 

void C2HPacketHandler_8723B(struct adapter *padapter, u8 *pbuffer, u16 length)
{
	C2H_EVT_HDR	C2hEvent;
	u8 *tmpBuf = NULL;
#ifdef CONFIG_WOWLAN
	struct pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);

	if (pwrpriv->wowlan_mode == true) {
		DBG_871X("%s(): return because wowolan_mode ==true! CMDID =%d\n", __func__, pbuffer[0]);
		return;
	}
#endif
	C2hEvent.CmdID = pbuffer[0];
	C2hEvent.CmdSeq = pbuffer[1];
	C2hEvent.CmdLen = length-2;
	tmpBuf = pbuffer+2;

	/* DBG_871X("%s C2hEvent.CmdID:%x C2hEvent.CmdLen:%x C2hEvent.CmdSeq:%x\n", */
	/* 		__func__, C2hEvent.CmdID, C2hEvent.CmdLen, C2hEvent.CmdSeq); */
	RT_PRINT_DATA(_module_hal_init_c_, _drv_notice_, "C2HPacketHandler_8723B(): Command Content:\n", tmpBuf, C2hEvent.CmdLen);

	process_c2h_event(padapter, &C2hEvent, tmpBuf);
	/* c2h_handler_8723b(padapter,&C2hEvent); */
	return;
}