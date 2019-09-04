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
typedef  size_t u32 ;
struct usb_device {int dummy; } ;
struct dvobj_priv {struct usb_device* pusbdev; int /*<<< orphan*/ * if1; } ;
typedef  int /*<<< orphan*/  _adapter ;
struct TYPE_3__ {int* Queue2EPNum; int /*<<< orphan*/  RtIntInPipe; int /*<<< orphan*/  RtBulkInPipe; } ;
typedef  TYPE_1__ HAL_DATA_TYPE ;

/* Variables and functions */
 TYPE_1__* GET_HAL_DATA (int /*<<< orphan*/ *) ; 
 size_t HW_QUEUE_ENTRY ; 
 size_t RECV_BULK_IN_ADDR ; 
 size_t RECV_INT_IN_ADDR ; 
 unsigned int usb_rcvbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndbulkpipe (struct usb_device*,int) ; 

unsigned int ffaddr2pipehdl(struct dvobj_priv *pdvobj, u32 addr)
{
	unsigned int pipe=0;
	int ep_num=0;
	_adapter *padapter = pdvobj->if1;
	struct usb_device *pusbd = pdvobj->pusbdev;	
	HAL_DATA_TYPE *pHalData = GET_HAL_DATA(padapter);

	if (addr == RECV_BULK_IN_ADDR) {	
		pipe=usb_rcvbulkpipe(pusbd, pHalData->RtBulkInPipe);
		
	} else if (addr == RECV_INT_IN_ADDR) {	
		pipe=usb_rcvbulkpipe(pusbd, pHalData->RtIntInPipe);
		
	} else if (addr < HW_QUEUE_ENTRY) {
		ep_num = pHalData->Queue2EPNum[addr];	
		pipe = usb_sndbulkpipe(pusbd, ep_num);
	}

	return pipe;
}