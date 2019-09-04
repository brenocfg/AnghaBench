#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct recv_priv {int /*<<< orphan*/  free_recv_buf_queue_cnt; int /*<<< orphan*/  ff_hwaddr; scalar_t__ precv_buf; } ;
struct recv_buf {int dummy; } ;
struct intf_hdl {int dummy; } ;
struct _adapter {struct recv_priv recvpriv; TYPE_1__* pio_queue; } ;
struct TYPE_2__ {struct intf_hdl intf; } ;

/* Variables and functions */
 scalar_t__ NR_RECVBUFF ; 
 int /*<<< orphan*/  RTL8712_DMA_RX0FF ; 
 unsigned int _FAIL ; 
 unsigned int _SUCCESS ; 
 int r8712_usb_read_port (struct intf_hdl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 

unsigned int r8712_usb_inirp_init(struct _adapter *padapter)
{
	u8 i;
	struct recv_buf *precvbuf;
	struct intf_hdl *pintfhdl = &padapter->pio_queue->intf;
	struct recv_priv *precvpriv = &(padapter->recvpriv);

	precvpriv->ff_hwaddr = RTL8712_DMA_RX0FF; /* mapping rx fifo address */
	/* issue Rx irp to receive data */
	precvbuf = (struct recv_buf *)precvpriv->precv_buf;
	for (i = 0; i < NR_RECVBUFF; i++) {
		if (r8712_usb_read_port(pintfhdl, precvpriv->ff_hwaddr, 0,
		   (unsigned char *)precvbuf) == false)
			return _FAIL;
		precvbuf++;
		precvpriv->free_recv_buf_queue_cnt--;
	}
	return _SUCCESS;
}