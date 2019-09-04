#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct usb_device {int dummy; } ;
struct urb {int /*<<< orphan*/  status; } ;
struct recv_priv {int /*<<< orphan*/  free_recv_skb_queue; } ;
struct recv_buf {int reuse; TYPE_2__* pskb; struct urb* purb; } ;
struct dvobj_priv {struct usb_device* pusbdev; } ;
struct TYPE_4__ {scalar_t__ pnp_bstop_trx; } ;
struct adapter {int /*<<< orphan*/  pnetdev; TYPE_1__ pwrctrlpriv; scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; struct recv_priv recvpriv; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*,...) ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MAX_RECVBUF_SZ ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 unsigned int ffaddr2pipehdl (struct dvobj_priv*,int /*<<< orphan*/ ) ; 
 TYPE_2__* netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct recv_buf*) ; 
 int /*<<< orphan*/  usb_read_port_complete ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

u32 usb_read_port(struct adapter *adapter, u32 addr, struct recv_buf *precvbuf)
{
	struct urb *purb = NULL;
	struct dvobj_priv	*pdvobj = adapter_to_dvobj(adapter);
	struct recv_priv	*precvpriv = &adapter->recvpriv;
	struct usb_device	*pusbd = pdvobj->pusbdev;
	int err;
	unsigned int pipe;
	u32 ret = _SUCCESS;

	if (adapter->bDriverStopped || adapter->bSurpriseRemoved ||
	    adapter->pwrctrlpriv.pnp_bstop_trx) {
		RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
			 ("usb_read_port:(adapt->bDriverStopped ||adapt->bSurpriseRemoved ||adapter->pwrctrlpriv.pnp_bstop_trx)!!!\n"));
		return _FAIL;
	}

	if (!precvbuf) {
		RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
			 ("usb_read_port:precvbuf==NULL\n"));
		return _FAIL;
	}

	if (!precvbuf->reuse || !precvbuf->pskb) {
		precvbuf->pskb = skb_dequeue(&precvpriv->free_recv_skb_queue);
		if (precvbuf->pskb)
			precvbuf->reuse = true;
	}

	/* re-assign for linux based on skb */
	if (!precvbuf->reuse || !precvbuf->pskb) {
		precvbuf->pskb = netdev_alloc_skb(adapter->pnetdev, MAX_RECVBUF_SZ);
		if (!precvbuf->pskb) {
			RT_TRACE(_module_hci_ops_os_c_, _drv_err_, ("init_recvbuf(): alloc_skb fail!\n"));
			DBG_88E("#### usb_read_port() alloc_skb fail!#####\n");
			return _FAIL;
		}
	} else { /* reuse skb */
		precvbuf->reuse = false;
	}

	purb = precvbuf->purb;

	/* translate DMA FIFO addr to pipehandle */
	pipe = ffaddr2pipehdl(pdvobj, addr);

	usb_fill_bulk_urb(purb, pusbd, pipe,
			  precvbuf->pskb->data,
			  MAX_RECVBUF_SZ,
			  usb_read_port_complete,
			  precvbuf);/* context is precvbuf */

	err = usb_submit_urb(purb, GFP_ATOMIC);
	if ((err) && (err != (-EPERM))) {
		RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
			 ("cannot submit rx in-token(err=0x%.8x), URB_STATUS =0x%.8x",
			 err, purb->status));
		DBG_88E("cannot submit rx in-token(err = 0x%08x),urb_status = %d\n",
			err, purb->status);
		ret = _FAIL;
	}

	return ret;
}