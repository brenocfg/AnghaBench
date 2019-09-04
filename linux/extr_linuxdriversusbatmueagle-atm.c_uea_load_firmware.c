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
struct usb_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ADI930 132 
 char* ADI930_FIRMWARE ; 
 char* EAGLE_FIRMWARE ; 
#define  EAGLE_I 131 
#define  EAGLE_II 130 
#define  EAGLE_III 129 
 char* EAGLE_III_FIRMWARE ; 
 char* EAGLE_II_FIRMWARE ; 
#define  EAGLE_IV 128 
 char* EAGLE_IV_FIRMWARE ; 
 char* EAGLE_I_FIRMWARE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_enters (struct usb_device*) ; 
 int /*<<< orphan*/  uea_err (struct usb_device*,char*,char*) ; 
 int /*<<< orphan*/  uea_info (struct usb_device*,char*,...) ; 
 int /*<<< orphan*/  uea_leaves (struct usb_device*) ; 
 int /*<<< orphan*/  uea_upload_pre_firmware ; 

__attribute__((used)) static int uea_load_firmware(struct usb_device *usb, unsigned int ver)
{
	int ret;
	char *fw_name = EAGLE_FIRMWARE;

	uea_enters(usb);
	uea_info(usb, "pre-firmware device, uploading firmware\n");

	switch (ver) {
	case ADI930:
		fw_name = ADI930_FIRMWARE;
		break;
	case EAGLE_I:
		fw_name = EAGLE_I_FIRMWARE;
		break;
	case EAGLE_II:
		fw_name = EAGLE_II_FIRMWARE;
		break;
	case EAGLE_III:
		fw_name = EAGLE_III_FIRMWARE;
		break;
	case EAGLE_IV:
		fw_name = EAGLE_IV_FIRMWARE;
		break;
	}

	ret = request_firmware_nowait(THIS_MODULE, 1, fw_name, &usb->dev,
					GFP_KERNEL, usb,
					uea_upload_pre_firmware);
	if (ret)
		uea_err(usb, "firmware %s is not available\n", fw_name);
	else
		uea_info(usb, "loading firmware %s\n", fw_name);

	uea_leaves(usb);
	return ret;
}