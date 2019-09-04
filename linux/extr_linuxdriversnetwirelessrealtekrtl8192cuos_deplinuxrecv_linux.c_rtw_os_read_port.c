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
struct recv_priv {int dummy; } ;
struct recv_buf {int dummy; } ;
struct TYPE_3__ {struct recv_priv recvpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */

void rtw_os_read_port(_adapter *padapter, struct recv_buf *precvbuf)
{
	struct recv_priv *precvpriv = &padapter->recvpriv;

#ifdef CONFIG_USB_HCI

	precvbuf->ref_cnt--;

	//free skb in recv_buf
	rtw_skb_free(precvbuf->pskb);

	precvbuf->pskb = NULL;
	precvbuf->reuse = _FALSE;

	if(precvbuf->irp_pending == _FALSE)
	{
		rtw_read_port(padapter, precvpriv->ff_hwaddr, 0, (unsigned char *)precvbuf);
	}


#endif
#ifdef CONFIG_SDIO_HCI
		precvbuf->pskb = NULL;
#endif

}