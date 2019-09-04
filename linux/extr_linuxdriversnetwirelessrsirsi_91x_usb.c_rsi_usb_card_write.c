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
typedef  int u8 ;
typedef  int u16 ;
struct rsi_hw {scalar_t__ rsi_dev; } ;
struct rsi_91x_usbdev {int* tx_buffer; int* bulkout_endpoint_addr; int write_fail; int /*<<< orphan*/  usbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_ZONE ; 
 int HZ ; 
 int RSI_USB_TX_HEAD_ROOM ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rsi_usb_card_write(struct rsi_hw *adapter,
			      u8 *buf,
			      u16 len,
			      u8 endpoint)
{
	struct rsi_91x_usbdev *dev = (struct rsi_91x_usbdev *)adapter->rsi_dev;
	int status;
	u8 *seg = dev->tx_buffer;
	int transfer;
	int ep = dev->bulkout_endpoint_addr[endpoint - 1];

	memset(seg, 0, len + RSI_USB_TX_HEAD_ROOM);
	memcpy(seg + RSI_USB_TX_HEAD_ROOM, buf, len);
	len += RSI_USB_TX_HEAD_ROOM;
	transfer = len;
	status = usb_bulk_msg(dev->usbdev,
			      usb_sndbulkpipe(dev->usbdev, ep),
			      (void *)seg,
			      (int)len,
			      &transfer,
			      HZ * 5);

	if (status < 0) {
		rsi_dbg(ERR_ZONE,
			"Card write failed with error code :%10d\n", status);
		dev->write_fail = 1;
	}
	return status;
}