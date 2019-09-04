#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {struct usb_host_interface* altsetting; } ;
struct TYPE_3__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int bEndpointAddress; int bmAttributes; void* wMaxPacketSize; } ;
struct rsi_hw {scalar_t__ rsi_dev; } ;
struct rsi_91x_usbdev {int* bulkin_endpoint_addr; int* bulkout_endpoint_addr; void** bulkout_size; void** bulkin_size; } ;
typedef  void* __le16 ;
struct TYPE_4__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_BULK_EP ; 
 int USB_DIR_IN ; 
 int USB_ENDPOINT_XFERTYPE_MASK ; 
 int USB_ENDPOINT_XFER_BULK ; 

__attribute__((used)) static int rsi_find_bulk_in_and_out_endpoints(struct usb_interface *interface,
					      struct rsi_hw *adapter)
{
	struct rsi_91x_usbdev *dev = (struct rsi_91x_usbdev *)adapter->rsi_dev;
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;
	__le16 buffer_size;
	int ii, bin_found = 0, bout_found = 0;

	iface_desc = &(interface->altsetting[0]);

	for (ii = 0; ii < iface_desc->desc.bNumEndpoints; ++ii) {
		endpoint = &(iface_desc->endpoint[ii].desc);

		if (!dev->bulkin_endpoint_addr[bin_found] &&
		    (endpoint->bEndpointAddress & USB_DIR_IN) &&
		    ((endpoint->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
		    USB_ENDPOINT_XFER_BULK)) {
			buffer_size = endpoint->wMaxPacketSize;
			dev->bulkin_size[bin_found] = buffer_size;
			dev->bulkin_endpoint_addr[bin_found] =
				endpoint->bEndpointAddress;
			bin_found++;
		}

		if (!dev->bulkout_endpoint_addr[bout_found] &&
		    !(endpoint->bEndpointAddress & USB_DIR_IN) &&
		    ((endpoint->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
		    USB_ENDPOINT_XFER_BULK)) {
			buffer_size = endpoint->wMaxPacketSize;
			dev->bulkout_endpoint_addr[bout_found] =
				endpoint->bEndpointAddress;
			dev->bulkout_size[bout_found] = buffer_size;
			bout_found++;
		}

		if (bin_found >= MAX_BULK_EP || bout_found >= MAX_BULK_EP)
			break;
	}

	if (!(dev->bulkin_endpoint_addr[0]) &&
	    dev->bulkout_endpoint_addr[0])
		return -EINVAL;

	return 0;
}