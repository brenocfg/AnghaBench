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
typedef  int u32 ;
struct usb_device {int dummy; } ;
struct dvobj_priv {int nr_endpoint; struct usb_device* pusbdev; } ;

/* Variables and functions */
#define  RTL8712_DMA_BCNQ 137 
#define  RTL8712_DMA_BEQ 136 
#define  RTL8712_DMA_BKQ 135 
#define  RTL8712_DMA_BMCQ 134 
#define  RTL8712_DMA_C2HCMD 133 
#define  RTL8712_DMA_H2CCMD 132 
#define  RTL8712_DMA_MGTQ 131 
#define  RTL8712_DMA_RX0FF 130 
#define  RTL8712_DMA_VIQ 129 
#define  RTL8712_DMA_VOQ 128 
 unsigned int usb_rcvbulkpipe (struct usb_device*,int) ; 
 unsigned int usb_sndbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static unsigned int ffaddr2pipehdl(struct dvobj_priv *pdvobj, u32 addr)
{
	unsigned int pipe = 0;
	struct usb_device *pusbd = pdvobj->pusbdev;

	if (pdvobj->nr_endpoint == 11) {
		switch (addr) {
		case RTL8712_DMA_BKQ:
			pipe = usb_sndbulkpipe(pusbd, 0x07);
			break;
		case RTL8712_DMA_BEQ:
			pipe = usb_sndbulkpipe(pusbd, 0x06);
			break;
		case RTL8712_DMA_VIQ:
			pipe = usb_sndbulkpipe(pusbd, 0x05);
			break;
		case RTL8712_DMA_VOQ:
			pipe = usb_sndbulkpipe(pusbd, 0x04);
			break;
		case RTL8712_DMA_BCNQ:
			pipe = usb_sndbulkpipe(pusbd, 0x0a);
			break;
		case RTL8712_DMA_BMCQ:	/* HI Queue */
			pipe = usb_sndbulkpipe(pusbd, 0x0b);
			break;
		case RTL8712_DMA_MGTQ:
			pipe = usb_sndbulkpipe(pusbd, 0x0c);
			break;
		case RTL8712_DMA_RX0FF:
			pipe = usb_rcvbulkpipe(pusbd, 0x03); /* in */
			break;
		case RTL8712_DMA_C2HCMD:
			pipe = usb_rcvbulkpipe(pusbd, 0x09); /* in */
			break;
		case RTL8712_DMA_H2CCMD:
			pipe = usb_sndbulkpipe(pusbd, 0x0d);
			break;
		}
	} else if (pdvobj->nr_endpoint == 6) {
		switch (addr) {
		case RTL8712_DMA_BKQ:
			pipe = usb_sndbulkpipe(pusbd, 0x07);
			break;
		case RTL8712_DMA_BEQ:
			pipe = usb_sndbulkpipe(pusbd, 0x06);
			break;
		case RTL8712_DMA_VIQ:
			pipe = usb_sndbulkpipe(pusbd, 0x05);
			break;
		case RTL8712_DMA_VOQ:
			pipe = usb_sndbulkpipe(pusbd, 0x04);
			break;
		case RTL8712_DMA_RX0FF:
		case RTL8712_DMA_C2HCMD:
			pipe = usb_rcvbulkpipe(pusbd, 0x03); /* in */
			break;
		case RTL8712_DMA_H2CCMD:
		case RTL8712_DMA_BCNQ:
		case RTL8712_DMA_BMCQ:
		case RTL8712_DMA_MGTQ:
			pipe = usb_sndbulkpipe(pusbd, 0x0d);
			break;
		}
	} else if (pdvobj->nr_endpoint == 4) {
		switch (addr) {
		case RTL8712_DMA_BEQ:
			pipe = usb_sndbulkpipe(pusbd, 0x06);
			break;
		case RTL8712_DMA_VOQ:
			pipe = usb_sndbulkpipe(pusbd, 0x04);
			break;
		case RTL8712_DMA_RX0FF:
		case RTL8712_DMA_C2HCMD:
			pipe = usb_rcvbulkpipe(pusbd, 0x03); /* in */
			break;
		case RTL8712_DMA_H2CCMD:
		case RTL8712_DMA_BCNQ:
		case RTL8712_DMA_BMCQ:
		case RTL8712_DMA_MGTQ:
			pipe = usb_sndbulkpipe(pusbd, 0x0d);
			break;
		}
	} else {
		pipe = 0;
	}
	return pipe;
}