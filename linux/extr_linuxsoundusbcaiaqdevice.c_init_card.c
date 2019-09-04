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
typedef  int /*<<< orphan*/  usbpath ;
struct TYPE_4__ {int /*<<< orphan*/  iProduct; int /*<<< orphan*/  iManufacturer; } ;
struct usb_device {TYPE_2__ descriptor; } ;
struct TYPE_3__ {struct snd_card* card; struct usb_device* dev; } ;
struct snd_usb_caiaqdev {char* vendor_name; char* product_name; int /*<<< orphan*/  ep1_in_urb; int /*<<< orphan*/  spec_received; int /*<<< orphan*/  ep1_wait_queue; int /*<<< orphan*/  prepare_wait_queue; int /*<<< orphan*/  midi_out_urb; int /*<<< orphan*/  midi_out_buf; int /*<<< orphan*/  ep1_in_buf; TYPE_1__ chip; } ;
struct snd_card {char* driver; char* shortname; char* mixername; char* id; int /*<<< orphan*/  longname; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 int /*<<< orphan*/  CAIAQ_USB_STR_LEN ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  EP1_BUFSIZE ; 
 int /*<<< orphan*/  EP1_CMD_GET_DEVICE_INFO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 char* MODNAME ; 
 struct device* caiaqdev_to_dev (struct snd_usb_caiaqdev*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_card (struct snd_usb_caiaqdev*) ; 
 int /*<<< orphan*/  snd_card_set_id (struct snd_card*,char*) ; 
 int /*<<< orphan*/  snd_usb_caiaq_midi_output_done ; 
 int snd_usb_caiaq_send_command (struct snd_usb_caiaqdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  usb_ep1_command_reply_dispatch ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ *,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_usb_caiaqdev*) ; 
 int /*<<< orphan*/  usb_init_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,char*,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int) ; 
 scalar_t__ usb_set_interface (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_string (struct usb_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_submit_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_urb_ep_type_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_card(struct snd_usb_caiaqdev *cdev)
{
	char *c, usbpath[32];
	struct usb_device *usb_dev = cdev->chip.dev;
	struct snd_card *card = cdev->chip.card;
	struct device *dev = caiaqdev_to_dev(cdev);
	int err, len;

	if (usb_set_interface(usb_dev, 0, 1) != 0) {
		dev_err(dev, "can't set alt interface.\n");
		return -EIO;
	}

	usb_init_urb(&cdev->ep1_in_urb);
	usb_init_urb(&cdev->midi_out_urb);

	usb_fill_bulk_urb(&cdev->ep1_in_urb, usb_dev,
			  usb_rcvbulkpipe(usb_dev, 0x1),
			  cdev->ep1_in_buf, EP1_BUFSIZE,
			  usb_ep1_command_reply_dispatch, cdev);

	usb_fill_bulk_urb(&cdev->midi_out_urb, usb_dev,
			  usb_sndbulkpipe(usb_dev, 0x1),
			  cdev->midi_out_buf, EP1_BUFSIZE,
			  snd_usb_caiaq_midi_output_done, cdev);

	/* sanity checks of EPs before actually submitting */
	if (usb_urb_ep_type_check(&cdev->ep1_in_urb) ||
	    usb_urb_ep_type_check(&cdev->midi_out_urb)) {
		dev_err(dev, "invalid EPs\n");
		return -EINVAL;
	}

	init_waitqueue_head(&cdev->ep1_wait_queue);
	init_waitqueue_head(&cdev->prepare_wait_queue);

	if (usb_submit_urb(&cdev->ep1_in_urb, GFP_KERNEL) != 0)
		return -EIO;

	err = snd_usb_caiaq_send_command(cdev, EP1_CMD_GET_DEVICE_INFO, NULL, 0);
	if (err)
		goto err_kill_urb;

	if (!wait_event_timeout(cdev->ep1_wait_queue, cdev->spec_received, HZ)) {
		err = -ENODEV;
		goto err_kill_urb;
	}

	usb_string(usb_dev, usb_dev->descriptor.iManufacturer,
		   cdev->vendor_name, CAIAQ_USB_STR_LEN);

	usb_string(usb_dev, usb_dev->descriptor.iProduct,
		   cdev->product_name, CAIAQ_USB_STR_LEN);

	strlcpy(card->driver, MODNAME, sizeof(card->driver));
	strlcpy(card->shortname, cdev->product_name, sizeof(card->shortname));
	strlcpy(card->mixername, cdev->product_name, sizeof(card->mixername));

	/* if the id was not passed as module option, fill it with a shortened
	 * version of the product string which does not contain any
	 * whitespaces */

	if (*card->id == '\0') {
		char id[sizeof(card->id)];

		memset(id, 0, sizeof(id));

		for (c = card->shortname, len = 0;
			*c && len < sizeof(card->id); c++)
			if (*c != ' ')
				id[len++] = *c;

		snd_card_set_id(card, id);
	}

	usb_make_path(usb_dev, usbpath, sizeof(usbpath));
	snprintf(card->longname, sizeof(card->longname), "%s %s (%s)",
		       cdev->vendor_name, cdev->product_name, usbpath);

	setup_card(cdev);
	return 0;

 err_kill_urb:
	usb_kill_urb(&cdev->ep1_in_urb);
	return err;
}