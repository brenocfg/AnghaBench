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
typedef  int /*<<< orphan*/  u8 ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct firmware {char* data; int size; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int FPGA_BUFSIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bitrev8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 
 int usb6fire_fw_ezusb_write (struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int usb6fire_fw_fpga_write (struct usb_device*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int usb6fire_fw_fpga_upload(
		struct usb_interface *intf, const char *fwname)
{
	int ret;
	int i;
	struct usb_device *device = interface_to_usbdev(intf);
	u8 *buffer = kmalloc(FPGA_BUFSIZE, GFP_KERNEL);
	const char *c;
	const char *end;
	const struct firmware *fw;

	if (!buffer)
		return -ENOMEM;

	ret = request_firmware(&fw, fwname, &device->dev);
	if (ret < 0) {
		dev_err(&intf->dev, "unable to get fpga firmware %s.\n",
				fwname);
		kfree(buffer);
		return -EIO;
	}

	c = fw->data;
	end = fw->data + fw->size;

	ret = usb6fire_fw_ezusb_write(device, 8, 0, NULL, 0);
	if (ret < 0) {
		kfree(buffer);
		release_firmware(fw);
		dev_err(&intf->dev,
			"unable to upload fpga firmware: begin urb.\n");
		return ret;
	}

	while (c != end) {
		for (i = 0; c != end && i < FPGA_BUFSIZE; i++, c++)
			buffer[i] = bitrev8((u8)*c);

		ret = usb6fire_fw_fpga_write(device, buffer, i);
		if (ret < 0) {
			release_firmware(fw);
			kfree(buffer);
			dev_err(&intf->dev,
				"unable to upload fpga firmware: fw urb.\n");
			return ret;
		}
	}
	release_firmware(fw);
	kfree(buffer);

	ret = usb6fire_fw_ezusb_write(device, 9, 0, NULL, 0);
	if (ret < 0) {
		dev_err(&intf->dev,
			"unable to upload fpga firmware: end urb.\n");
		return ret;
	}
	return 0;
}