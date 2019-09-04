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
struct xmit_priv {int /*<<< orphan*/ * SdioXmitThread; int /*<<< orphan*/  SdioXmitTerminateSema; int /*<<< orphan*/  SdioXmitSema; } ;
struct adapter {struct xmit_priv xmitpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void rtl8723b_stop_thread(struct adapter *padapter)
{
#ifndef CONFIG_SDIO_TX_TASKLET
	struct xmit_priv *xmitpriv = &padapter->xmitpriv;

	/*  stop xmit_buf_thread */
	if (xmitpriv->SdioXmitThread) {
		up(&xmitpriv->SdioXmitSema);
		down(&xmitpriv->SdioXmitTerminateSema);
		xmitpriv->SdioXmitThread = NULL;
	}
#endif
}