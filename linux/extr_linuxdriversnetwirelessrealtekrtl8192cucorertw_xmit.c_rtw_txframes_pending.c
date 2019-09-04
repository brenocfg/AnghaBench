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
struct xmit_priv {int /*<<< orphan*/  vo_pending; int /*<<< orphan*/  vi_pending; int /*<<< orphan*/  bk_pending; int /*<<< orphan*/  be_pending; } ;
typedef  int s32 ;
struct TYPE_3__ {struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 scalar_t__ _FALSE ; 
 scalar_t__ _rtw_queue_empty (int /*<<< orphan*/ *) ; 

s32 rtw_txframes_pending(_adapter *padapter)
{
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;

	return ((_rtw_queue_empty(&pxmitpriv->be_pending) == _FALSE) || 
			 (_rtw_queue_empty(&pxmitpriv->bk_pending) == _FALSE) || 
			 (_rtw_queue_empty(&pxmitpriv->vi_pending) == _FALSE) ||
			 (_rtw_queue_empty(&pxmitpriv->vo_pending) == _FALSE));
}