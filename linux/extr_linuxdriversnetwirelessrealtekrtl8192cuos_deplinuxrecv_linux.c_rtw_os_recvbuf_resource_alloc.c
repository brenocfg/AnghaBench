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
struct recv_buf {int dummy; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int _SUCCESS ; 

int rtw_os_recvbuf_resource_alloc(_adapter *padapter, struct recv_buf *precvbuf)
{
	int res=_SUCCESS;

#ifdef CONFIG_USB_HCI
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);
	struct usb_device	*pusbd = pdvobjpriv->pusbdev;

	precvbuf->irp_pending = _FALSE;
	precvbuf->purb = usb_alloc_urb(0, GFP_KERNEL);
	if(precvbuf->purb == NULL){
		res = _FAIL;
	}

	precvbuf->pskb = NULL;

	precvbuf->reuse = _FALSE;

	precvbuf->pallocated_buf  = precvbuf->pbuf = NULL;

	precvbuf->pdata = precvbuf->phead = precvbuf->ptail = precvbuf->pend = NULL;

	precvbuf->transfer_len = 0;

	precvbuf->len = 0;

	#ifdef CONFIG_USE_USB_BUFFER_ALLOC_RX
	precvbuf->pallocated_buf = rtw_usb_buffer_alloc(pusbd, (size_t)precvbuf->alloc_sz, &precvbuf->dma_transfer_addr);
	precvbuf->pbuf = precvbuf->pallocated_buf;
	if(precvbuf->pallocated_buf == NULL)
		return _FAIL;
	#endif //CONFIG_USE_USB_BUFFER_ALLOC_RX
	
#endif //CONFIG_USB_HCI

	return res;
}