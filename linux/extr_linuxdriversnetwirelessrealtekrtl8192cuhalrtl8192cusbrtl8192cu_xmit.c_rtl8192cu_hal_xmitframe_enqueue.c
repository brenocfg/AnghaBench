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
struct xmit_priv {int /*<<< orphan*/  tx_drop; int /*<<< orphan*/  tx_pkts; } ;
struct xmit_frame {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  rtw_free_xmitframe (struct xmit_priv*,struct xmit_frame*) ; 
 int /*<<< orphan*/  rtw_xmitframe_enqueue (TYPE_1__*,struct xmit_frame*) ; 

s32	 rtl8192cu_hal_xmitframe_enqueue(_adapter *padapter, struct xmit_frame *pxmitframe)
{
	struct xmit_priv 	*pxmitpriv = &padapter->xmitpriv;
	s32 err;
	
	if ((err=rtw_xmitframe_enqueue(padapter, pxmitframe)) != _SUCCESS) 
	{
		rtw_free_xmitframe(pxmitpriv, pxmitframe);

		// Trick, make the statistics correct
		pxmitpriv->tx_pkts--;
		pxmitpriv->tx_drop++;					
	}
	else
	{
#ifdef PLATFORM_LINUX
		tasklet_hi_schedule(&pxmitpriv->xmit_tasklet);
#endif
	}
	
	return err;
	
}