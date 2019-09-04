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
 int _SUCCESS ; 

int rtw_os_xmit_resource_alloc(_adapter *padapter, struct xmit_buf *pxmitbuf,u32 alloc_sz)
{
#ifdef CONFIG_USB_HCI
	int i;
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);
	struct usb_device	*pusbd = pdvobjpriv->pusbdev;

#ifdef CONFIG_USE_USB_BUFFER_ALLOC_TX
	pxmitbuf->pallocated_buf = rtw_usb_buffer_alloc(pusbd, (size_t)alloc_sz, &pxmitbuf->dma_transfer_addr);
	pxmitbuf->pbuf = pxmitbuf->pallocated_buf;
	if(pxmitbuf->pallocated_buf == NULL)
		return _FAIL;
#else // CONFIG_USE_USB_BUFFER_ALLOC_TX
	
	pxmitbuf->pallocated_buf = rtw_zmalloc(alloc_sz);
	if (pxmitbuf->pallocated_buf == NULL)
	{
		return _FAIL;
	}

	pxmitbuf->pbuf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(pxmitbuf->pallocated_buf), XMITBUF_ALIGN_SZ);
	pxmitbuf->dma_transfer_addr = 0;

#endif // CONFIG_USE_USB_BUFFER_ALLOC_TX

	for(i=0; i<8; i++)
      	{
      		pxmitbuf->pxmit_urb[i] = usb_alloc_urb(0, GFP_KERNEL);
             	if(pxmitbuf->pxmit_urb[i] == NULL) 
             	{
             		DBG_871X("pxmitbuf->pxmit_urb[i]==NULL");
	        	return _FAIL;	 
             	}      		  	
	
      	}
#endif
#if defined(CONFIG_PCI_HCI) || defined(CONFIG_SDIO_HCI)
	pxmitbuf->pallocated_buf = rtw_zmalloc(alloc_sz);
	if (pxmitbuf->pallocated_buf == NULL)
	{
		return _FAIL;
	}

	pxmitbuf->pbuf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(pxmitbuf->pallocated_buf), XMITBUF_ALIGN_SZ);
#endif

	return _SUCCESS;	
}