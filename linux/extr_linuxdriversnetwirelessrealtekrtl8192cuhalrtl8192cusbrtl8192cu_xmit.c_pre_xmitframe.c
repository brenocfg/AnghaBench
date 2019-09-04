#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct xmit_priv {int /*<<< orphan*/  tx_drop; int /*<<< orphan*/  tx_pkts; int /*<<< orphan*/  lock; } ;
struct pkt_attrib {int dummy; } ;
struct xmit_frame {int /*<<< orphan*/  buf_addr; struct xmit_buf* pxmitbuf; struct pkt_attrib attrib; } ;
struct xmit_buf {struct xmit_frame* priv_data; int /*<<< orphan*/  pbuf; } ;
struct mlme_priv {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_6__ {struct mlme_priv mlmepriv; struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _FALSE ; 
 int _FW_UNDER_LINKING ; 
 int _FW_UNDER_SURVEY ; 
 scalar_t__ _SUCCESS ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _module_xmit_osdep_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int) ; 
 struct xmit_buf* rtw_alloc_xmitbuf (struct xmit_priv*) ; 
 int /*<<< orphan*/  rtw_free_xmitbuf (struct xmit_priv*,struct xmit_buf*) ; 
 int /*<<< orphan*/  rtw_free_xmitframe (struct xmit_priv*,struct xmit_frame*) ; 
 scalar_t__ rtw_txframes_sta_ac_pending (TYPE_1__*,struct pkt_attrib*) ; 
 scalar_t__ rtw_xmitframe_enqueue (TYPE_1__*,struct xmit_frame*) ; 
 scalar_t__ xmitframe_direct (TYPE_1__*,struct xmit_frame*) ; 

__attribute__((used)) static s32 pre_xmitframe(_adapter *padapter, struct xmit_frame *pxmitframe)
{
        _irqL irqL;
	s32 res;
	struct xmit_buf *pxmitbuf = NULL;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct pkt_attrib *pattrib = &pxmitframe->attrib;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	
	
	_enter_critical_bh(&pxmitpriv->lock, &irqL);


	if (rtw_txframes_sta_ac_pending(padapter, pattrib) > 0)
		goto enqueue;


	if (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY|_FW_UNDER_LINKING) == _TRUE)
		goto enqueue;

#ifdef CONFIG_CONCURRENT_MODE	
	if (check_buddy_fwstate(padapter, _FW_UNDER_SURVEY|_FW_UNDER_LINKING) == _TRUE)
		goto enqueue;
#endif

	pxmitbuf = rtw_alloc_xmitbuf(pxmitpriv);
	if (pxmitbuf == NULL)
		goto enqueue;

	_exit_critical_bh(&pxmitpriv->lock, &irqL);

	pxmitframe->pxmitbuf = pxmitbuf;
	pxmitframe->buf_addr = pxmitbuf->pbuf;
	pxmitbuf->priv_data = pxmitframe;

	if (xmitframe_direct(padapter, pxmitframe) != _SUCCESS) {
		rtw_free_xmitbuf(pxmitpriv, pxmitbuf);
		rtw_free_xmitframe(pxmitpriv, pxmitframe);
	}

	return _TRUE;

enqueue:
	res = rtw_xmitframe_enqueue(padapter, pxmitframe);
	_exit_critical_bh(&pxmitpriv->lock, &irqL);

	if (res != _SUCCESS) {
		RT_TRACE(_module_xmit_osdep_c_, _drv_err_, ("pre_xmitframe: enqueue xmitframe fail\n"));
		rtw_free_xmitframe(pxmitpriv, pxmitframe);

		// Trick, make the statistics correct
		pxmitpriv->tx_pkts--;
		pxmitpriv->tx_drop++;
		return _TRUE;
	}

	return _FALSE;
}