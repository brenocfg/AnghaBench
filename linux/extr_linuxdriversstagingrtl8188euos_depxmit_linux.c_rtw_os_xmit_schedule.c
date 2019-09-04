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
struct xmit_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  xmit_tasklet; } ;
struct adapter {struct xmit_priv xmitpriv; } ;

/* Variables and functions */
 scalar_t__ rtw_txframes_pending (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

void rtw_os_xmit_schedule(struct adapter *padapter)
{
	struct xmit_priv *pxmitpriv;

	if (!padapter)
		return;

	pxmitpriv = &padapter->xmitpriv;

	spin_lock_bh(&pxmitpriv->lock);

	if (rtw_txframes_pending(padapter))
		tasklet_hi_schedule(&pxmitpriv->xmit_tasklet);

	spin_unlock_bh(&pxmitpriv->lock);
}