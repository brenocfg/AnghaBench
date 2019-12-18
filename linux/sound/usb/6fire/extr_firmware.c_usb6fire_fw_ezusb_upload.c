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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct ihex_record {int address; int* data; int len; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char const*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct ihex_record*) ; 
 struct ihex_record* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 
 int usb6fire_fw_ezusb_write (struct usb_device*,int,int,int*,int) ; 
 int usb6fire_fw_ihex_init (struct firmware const*,struct ihex_record*) ; 
 scalar_t__ usb6fire_fw_ihex_next_record (struct ihex_record*) ; 

__attribute__((used)) static int usb6fire_fw_ezusb_upload(
		struct usb_interface *intf, const char *fwname,
		unsigned int postaddr, u8 *postdata, unsigned int postlen)
{
	int ret;
	u8 data;
	struct usb_device *device = interface_to_usbdev(intf);
	const struct firmware *fw = NULL;
	struct ihex_record *rec = kmalloc(sizeof(struct ihex_record),
			GFP_KERNEL);

	if (!rec)
		return -ENOMEM;

	ret = request_firmware(&fw, fwname, &device->dev);
	if (ret < 0) {
		kfree(rec);
		dev_err(&intf->dev,
			"error requesting ezusb firmware %s.\n", fwname);
		return ret;
	}
	ret = usb6fire_fw_ihex_init(fw, rec);
	if (ret < 0) {
		kfree(rec);
		release_firmware(fw);
		dev_err(&intf->dev,
			"error validating ezusb firmware %s.\n", fwname);
		return ret;
	}
	/* upload firmware image */
	data = 0x01; /* stop ezusb cpu */
	ret = usb6fire_fw_ezusb_write(device, 0xa0, 0xe600, &data, 1);
	if (ret < 0) {
		kfree(rec);
		release_firmware(fw);
		dev_err(&intf->dev,
			"unable to upload ezusb firmware %s: begin message.\n",
			fwname);
		return ret;
	}

	while (usb6fire_fw_ihex_next_record(rec)) { /* write firmware */
		ret = usb6fire_fw_ezusb_write(device, 0xa0, rec->address,
				rec->data, rec->len);
		if (ret < 0) {
			kfree(rec);
			release_firmware(fw);
			dev_err(&intf->dev,
				"unable to upload ezusb firmware %s: data urb.\n",
				fwname);
			return ret;
		}
	}

	release_firmware(fw);
	kfree(rec);
	if (postdata) { /* write data after firmware has been uploaded */
		ret = usb6fire_fw_ezusb_write(device, 0xa0, postaddr,
				postdata, postlen);
		if (ret < 0) {
			dev_err(&intf->dev,
				"unable to upload ezusb firmware %s: post urb.\n",
				fwname);
			return ret;
		}
	}

	data = 0x00; /* resume ezusb cpu */
	ret = usb6fire_fw_ezusb_write(device, 0xa0, 0xe600, &data, 1);
	if (ret < 0) {
		dev_err(&intf->dev,
			"unable to upload ezusb firmware %s: end message.\n",
			fwname);
		return ret;
	}
	return 0;
}