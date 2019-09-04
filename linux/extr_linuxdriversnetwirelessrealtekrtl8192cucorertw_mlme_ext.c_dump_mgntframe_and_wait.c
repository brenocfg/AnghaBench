#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xmit_priv {int /*<<< orphan*/  lock_sctx; } ;
struct xmit_frame {struct xmit_buf* pxmitbuf; } ;
struct xmit_buf {struct submit_ctx* sctx; } ;
struct submit_ctx {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_4__ {scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _enter_critical (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_free_xmitbuf (struct xmit_priv*,struct xmit_buf*) ; 
 int /*<<< orphan*/  rtw_free_xmitframe (struct xmit_priv*,struct xmit_frame*) ; 
 scalar_t__ rtw_hal_mgnt_xmit (TYPE_1__*,struct xmit_frame*) ; 
 int /*<<< orphan*/  rtw_sctx_init (struct submit_ctx*,int) ; 
 scalar_t__ rtw_sctx_wait (struct submit_ctx*) ; 

s32 dump_mgntframe_and_wait(_adapter *padapter, struct xmit_frame *pmgntframe, int timeout_ms)
{
	s32 ret = _FAIL;
	_irqL irqL;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct xmit_buf *pxmitbuf = pmgntframe->pxmitbuf;
	struct submit_ctx sctx;

	if(padapter->bSurpriseRemoved == _TRUE ||
		padapter->bDriverStopped == _TRUE)
	{
		rtw_free_xmitbuf(&padapter->xmitpriv, pmgntframe->pxmitbuf);
		rtw_free_xmitframe(&padapter->xmitpriv, pmgntframe);
		return ret;
	}

	rtw_sctx_init(&sctx, timeout_ms);
	pxmitbuf->sctx = &sctx;

	ret = rtw_hal_mgnt_xmit(padapter, pmgntframe);

	if (ret == _SUCCESS)
		ret = rtw_sctx_wait(&sctx);

	_enter_critical(&pxmitpriv->lock_sctx, &irqL);
	pxmitbuf->sctx = NULL;
	_exit_critical(&pxmitpriv->lock_sctx, &irqL);

	 return ret;
}