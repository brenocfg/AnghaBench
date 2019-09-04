#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct usb_serial {TYPE_3__* interface; TYPE_2__* dev; } ;
struct usb_device_id {scalar_t__ driver_info; } ;
struct firmware {int* data; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  idProduct; } ;
struct TYPE_5__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_VENDOR_QUERY_FW_CONFIG ; 
 int /*<<< orphan*/  RQ_VENDOR_RESET_DEVICE ; 
 size_t VER_ADDR_1 ; 
 size_t VER_ADDR_2 ; 
 size_t VER_ADDR_3 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int mxuport_download_fw (struct usb_serial*,struct firmware const*) ; 
 int mxuport_get_fw_version (struct usb_serial*,int*) ; 
 int mxuport_send_ctrl_urb (struct usb_serial*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  usb_set_serial_data (struct usb_serial*,void*) ; 

__attribute__((used)) static int mxuport_probe(struct usb_serial *serial,
			 const struct usb_device_id *id)
{
	u16 productid = le16_to_cpu(serial->dev->descriptor.idProduct);
	const struct firmware *fw_p = NULL;
	u32 version;
	int local_ver;
	char buf[32];
	int err;

	/* Load our firmware */
	err = mxuport_send_ctrl_urb(serial, RQ_VENDOR_QUERY_FW_CONFIG, 0, 0);
	if (err) {
		mxuport_send_ctrl_urb(serial, RQ_VENDOR_RESET_DEVICE, 0, 0);
		return err;
	}

	err = mxuport_get_fw_version(serial, &version);
	if (err < 0)
		return err;

	dev_dbg(&serial->interface->dev, "Device firmware version v%x.%x.%x\n",
		(version & 0xff0000) >> 16,
		(version & 0xff00) >> 8,
		(version & 0xff));

	snprintf(buf, sizeof(buf) - 1, "moxa/moxa-%04x.fw", productid);

	err = request_firmware(&fw_p, buf, &serial->interface->dev);
	if (err) {
		dev_warn(&serial->interface->dev, "Firmware %s not found\n",
			 buf);

		/* Use the firmware already in the device */
		err = 0;
	} else {
		local_ver = ((fw_p->data[VER_ADDR_1] << 16) |
			     (fw_p->data[VER_ADDR_2] << 8) |
			     fw_p->data[VER_ADDR_3]);
		dev_dbg(&serial->interface->dev,
			"Available firmware version v%x.%x.%x\n",
			fw_p->data[VER_ADDR_1], fw_p->data[VER_ADDR_2],
			fw_p->data[VER_ADDR_3]);
		if (local_ver > version) {
			err = mxuport_download_fw(serial, fw_p);
			if (err)
				goto out;
			err  = mxuport_get_fw_version(serial, &version);
			if (err < 0)
				goto out;
		}
	}

	dev_info(&serial->interface->dev,
		 "Using device firmware version v%x.%x.%x\n",
		 (version & 0xff0000) >> 16,
		 (version & 0xff00) >> 8,
		 (version & 0xff));

	/*
	 * Contains the features of this hardware. Store away for
	 * later use, eg, number of ports.
	 */
	usb_set_serial_data(serial, (void *)id->driver_info);
out:
	if (fw_p)
		release_firmware(fw_p);
	return err;
}