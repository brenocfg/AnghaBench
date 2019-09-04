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
struct recv_buf {scalar_t__ purb; } ;
struct TYPE_2__ {scalar_t__ precv_buf; } ;
struct _adapter {TYPE_1__ recvpriv; } ;

/* Variables and functions */
 int NR_RECVBUFF ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

void r8712_usb_read_port_cancel(struct _adapter *padapter)
{
	int i;
	struct recv_buf *precvbuf;

	precvbuf = (struct recv_buf *)padapter->recvpriv.precv_buf;
	for (i = 0; i < NR_RECVBUFF; i++) {
		if (precvbuf->purb)
			usb_kill_urb(precvbuf->purb);
		precvbuf++;
	}
}