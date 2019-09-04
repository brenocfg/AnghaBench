#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usbatm_data {struct cxacru_data* driver_data; } ;
struct usb_interface {int dummy; } ;
struct firmware {int dummy; } ;
struct cxacru_data {TYPE_1__* modem_type; } ;
struct TYPE_2__ {scalar_t__ boot_rom_patch; } ;

/* Variables and functions */
 int cxacru_card_status (struct cxacru_data*) ; 
 int cxacru_find_firmware (struct cxacru_data*,char*,struct firmware const**) ; 
 int /*<<< orphan*/  cxacru_upload_firmware (struct cxacru_data*,struct firmware const*,struct firmware const*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int /*<<< orphan*/  usb_dbg (struct usbatm_data*,char*) ; 
 int /*<<< orphan*/  usb_warn (struct usbatm_data*,char*) ; 

__attribute__((used)) static int cxacru_heavy_init(struct usbatm_data *usbatm_instance,
			     struct usb_interface *usb_intf)
{
	const struct firmware *fw, *bp;
	struct cxacru_data *instance = usbatm_instance->driver_data;
	int ret = cxacru_find_firmware(instance, "fw", &fw);

	if (ret) {
		usb_warn(usbatm_instance, "firmware (cxacru-fw.bin) unavailable (system misconfigured?)\n");
		return ret;
	}

	if (instance->modem_type->boot_rom_patch) {
		ret = cxacru_find_firmware(instance, "bp", &bp);
		if (ret) {
			usb_warn(usbatm_instance, "boot ROM patch (cxacru-bp.bin) unavailable (system misconfigured?)\n");
			release_firmware(fw);
			return ret;
		}
	}

	cxacru_upload_firmware(instance, fw, bp);

	if (instance->modem_type->boot_rom_patch)
		release_firmware(bp);
	release_firmware(fw);

	ret = cxacru_card_status(instance);
	if (ret)
		usb_dbg(usbatm_instance, "modem initialisation failed\n");
	else
		usb_dbg(usbatm_instance, "done setting up the modem\n");

	return ret;
}