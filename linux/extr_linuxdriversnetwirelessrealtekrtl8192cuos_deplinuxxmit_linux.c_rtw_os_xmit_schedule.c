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
struct xmit_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  xmit_tasklet; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_4__ {struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rtw_txframes_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

void rtw_os_xmit_schedule(_adapter *padapter)
{
#ifdef CONFIG_SDIO_HCI
	if(!padapter)
		return;
	
	if (rtw_txframes_pending(padapter))
		_rtw_up_sema(&padapter->xmitpriv.xmit_sema);
#else
	_irqL  irqL;
	struct xmit_priv *pxmitpriv;

	if(!padapter)
		return;

	pxmitpriv = &padapter->xmitpriv;

	_enter_critical_bh(&pxmitpriv->lock, &irqL);

	if(rtw_txframes_pending(padapter))	
	{
		tasklet_hi_schedule(&pxmitpriv->xmit_tasklet);
	}

	_exit_critical_bh(&pxmitpriv->lock, &irqL);
#endif
}