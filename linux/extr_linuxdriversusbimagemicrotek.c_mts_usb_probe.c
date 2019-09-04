#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct TYPE_11__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_4__* endpoint; TYPE_2__ desc; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  idVendor; int /*<<< orphan*/  idProduct; } ;
struct usb_device {int /*<<< orphan*/  dev; TYPE_1__ descriptor; } ;
struct TYPE_14__ {struct mts_desc* scsi_status; } ;
struct mts_desc {int ep_out; int ep_response; int ep_image; int /*<<< orphan*/  urb; TYPE_5__ context; TYPE_6__* host; struct usb_interface* usb_intf; struct usb_device* usb_dev; } ;
typedef  int /*<<< orphan*/  new_desc ;
struct TYPE_15__ {unsigned long* hostdata; } ;
struct TYPE_12__ {int bmAttributes; int bEndpointAddress; } ;
struct TYPE_13__ {TYPE_3__ desc; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTS_DEBUG (char*,int,...) ; 
 int /*<<< orphan*/  MTS_DEBUG_GOT_HERE () ; 
 int MTS_EP_IMAGE ; 
 int MTS_EP_OUT ; 
 int MTS_EP_RESPONSE ; 
 int MTS_EP_TOTAL ; 
 int /*<<< orphan*/  MTS_WARNING (char*,...) ; 
 int USB_DIR_IN ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
 int USB_ENDPOINT_XFERTYPE_MASK ; 
 int USB_ENDPOINT_XFER_BULK ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct mts_desc*) ; 
 struct mts_desc* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct mts_desc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mts_scsi_host_template ; 
 scalar_t__ scsi_add_host (TYPE_6__*,int /*<<< orphan*/ *) ; 
 TYPE_6__* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (TYPE_6__*) ; 
 int /*<<< orphan*/  scsi_scan_host (TYPE_6__*) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct mts_desc*) ; 

__attribute__((used)) static int mts_usb_probe(struct usb_interface *intf,
			 const struct usb_device_id *id)
{
	int i;
	int ep_out = -1;
	int ep_in_set[3]; /* this will break if we have more than three endpoints
			   which is why we check */
	int *ep_in_current = ep_in_set;
	int err_retval = -ENOMEM;

	struct mts_desc * new_desc;
	struct usb_device *dev = interface_to_usbdev (intf);

	/* the current altsetting on the interface we're probing */
	struct usb_host_interface *altsetting;

	MTS_DEBUG_GOT_HERE();
	MTS_DEBUG( "usb-device descriptor at %x\n", (int)dev );

	MTS_DEBUG( "product id = 0x%x, vendor id = 0x%x\n",
		   le16_to_cpu(dev->descriptor.idProduct),
		   le16_to_cpu(dev->descriptor.idVendor) );

	MTS_DEBUG_GOT_HERE();

	/* the current altsetting on the interface we're probing */
	altsetting = intf->cur_altsetting;


	/* Check if the config is sane */

	if ( altsetting->desc.bNumEndpoints != MTS_EP_TOTAL ) {
		MTS_WARNING( "expecting %d got %d endpoints! Bailing out.\n",
			     (int)MTS_EP_TOTAL, (int)altsetting->desc.bNumEndpoints );
		return -ENODEV;
	}

	for( i = 0; i < altsetting->desc.bNumEndpoints; i++ ) {
		if ((altsetting->endpoint[i].desc.bmAttributes &
		     USB_ENDPOINT_XFERTYPE_MASK) != USB_ENDPOINT_XFER_BULK) {

			MTS_WARNING( "can only deal with bulk endpoints; endpoint %d is not bulk.\n",
			     (int)altsetting->endpoint[i].desc.bEndpointAddress );
		} else {
			if (altsetting->endpoint[i].desc.bEndpointAddress &
			    USB_DIR_IN)
				*ep_in_current++
					= altsetting->endpoint[i].desc.bEndpointAddress &
					USB_ENDPOINT_NUMBER_MASK;
			else {
				if ( ep_out != -1 ) {
					MTS_WARNING( "can only deal with one output endpoints. Bailing out." );
					return -ENODEV;
				}

				ep_out = altsetting->endpoint[i].desc.bEndpointAddress &
					USB_ENDPOINT_NUMBER_MASK;
			}
		}

	}


	if ( ep_out == -1 ) {
		MTS_WARNING( "couldn't find an output bulk endpoint. Bailing out.\n" );
		return -ENODEV;
	}


	new_desc = kzalloc(sizeof(struct mts_desc), GFP_KERNEL);
	if (!new_desc)
		goto out;

	new_desc->urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!new_desc->urb)
		goto out_kfree;

	new_desc->context.scsi_status = kmalloc(1, GFP_KERNEL);
	if (!new_desc->context.scsi_status)
		goto out_free_urb;

	new_desc->usb_dev = dev;
	new_desc->usb_intf = intf;

	/* endpoints */
	new_desc->ep_out = ep_out;
	new_desc->ep_response = ep_in_set[0];
	new_desc->ep_image = ep_in_set[1];

	if ( new_desc->ep_out != MTS_EP_OUT )
		MTS_WARNING( "will this work? Command EP is not usually %d\n",
			     (int)new_desc->ep_out );

	if ( new_desc->ep_response != MTS_EP_RESPONSE )
		MTS_WARNING( "will this work? Response EP is not usually %d\n",
			     (int)new_desc->ep_response );

	if ( new_desc->ep_image != MTS_EP_IMAGE )
		MTS_WARNING( "will this work? Image data EP is not usually %d\n",
			     (int)new_desc->ep_image );

	new_desc->host = scsi_host_alloc(&mts_scsi_host_template,
			sizeof(new_desc));
	if (!new_desc->host)
		goto out_kfree2;

	new_desc->host->hostdata[0] = (unsigned long)new_desc;
	if (scsi_add_host(new_desc->host, &dev->dev)) {
		err_retval = -EIO;
		goto out_host_put;
	}
	scsi_scan_host(new_desc->host);

	usb_set_intfdata(intf, new_desc);
	return 0;

 out_host_put:
	scsi_host_put(new_desc->host);
 out_kfree2:
	kfree(new_desc->context.scsi_status);
 out_free_urb:
	usb_free_urb(new_desc->urb);
 out_kfree:
	kfree(new_desc);
 out:
	return err_retval;
}