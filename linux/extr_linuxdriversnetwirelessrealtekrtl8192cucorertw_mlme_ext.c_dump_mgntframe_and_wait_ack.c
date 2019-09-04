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
struct xmit_frame {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  dump_mgntframe (int /*<<< orphan*/ *,struct xmit_frame*) ; 
 int /*<<< orphan*/  rtw_msleep_os (int) ; 

s32 dump_mgntframe_and_wait_ack(_adapter *padapter, struct xmit_frame *pmgntframe)
{
#ifdef CONFIG_XMIT_ACK
	s32 ret = _FAIL;
	u32 timeout_ms = 500;//  500ms
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	#ifdef CONFIG_CONCURRENT_MODE
	if (padapter->pbuddy_adapter && !padapter->isprimary)
		pxmitpriv = &(padapter->pbuddy_adapter->xmitpriv);
	#endif

	if(padapter->bSurpriseRemoved == _TRUE ||
		padapter->bDriverStopped == _TRUE)
	{
		rtw_free_xmitbuf(&padapter->xmitpriv, pmgntframe->pxmitbuf);
		rtw_free_xmitframe(&padapter->xmitpriv, pmgntframe);
		return -1;
	}

	_enter_critical_mutex(&pxmitpriv->ack_tx_mutex, NULL);
	pxmitpriv->ack_tx = _TRUE;

	pmgntframe->ack_report = 1;
	if (rtw_hal_mgnt_xmit(padapter, pmgntframe) == _SUCCESS) {
		ret = rtw_ack_tx_wait(pxmitpriv, timeout_ms);
	}

	pxmitpriv->ack_tx = _FALSE;
	_exit_critical_mutex(&pxmitpriv->ack_tx_mutex, NULL);

	 return ret;
#else //!CONFIG_XMIT_ACK
	dump_mgntframe(padapter, pmgntframe);
	rtw_msleep_os(50);
	return _SUCCESS;
#endif //!CONFIG_XMIT_ACK	 
}