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
typedef  int /*<<< orphan*/  u32 ;
struct xmit_buf {int dummy; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */

void rtw_os_xmit_resource_free(_adapter *padapter, struct xmit_buf *pxmitbuf,u32 free_sz)
{
#ifdef CONFIG_USB_HCI
	int i;
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);
	struct usb_device	*pusbd = pdvobjpriv->pusbdev;


	for(i=0; i<8; i++)
	{
		if(pxmitbuf->pxmit_urb[i])
		{
			//usb_kill_urb(pxmitbuf->pxmit_urb[i]);
			usb_free_urb(pxmitbuf->pxmit_urb[i]);
		}
	}

#ifdef CONFIG_USE_USB_BUFFER_ALLOC_TX
	rtw_usb_buffer_free(pusbd, (size_t)free_sz, pxmitbuf->pallocated_buf, pxmitbuf->dma_transfer_addr);
	pxmitbuf->pallocated_buf =  NULL;
	pxmitbuf->dma_transfer_addr = 0;
#else	// CONFIG_USE_USB_BUFFER_ALLOC_TX
	if(pxmitbuf->pallocated_buf)
		rtw_mfree(pxmitbuf->pallocated_buf, free_sz);
#endif	// CONFIG_USE_USB_BUFFER_ALLOC_TX

#endif
#if defined(CONFIG_PCI_HCI) || defined(CONFIG_SDIO_HCI)
	if(pxmitbuf->pallocated_buf)
		rtw_mfree(pxmitbuf->pallocated_buf, free_sz);
#endif
}