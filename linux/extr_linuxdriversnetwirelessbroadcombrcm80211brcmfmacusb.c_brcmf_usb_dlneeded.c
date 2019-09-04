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
typedef  int u32 ;
struct TYPE_2__ {int devid; int chiprev; } ;
struct brcmf_usbdev_info {TYPE_1__ bus_pub; } ;
struct bootrom_id_le {int /*<<< orphan*/  chiprev; int /*<<< orphan*/  chip; } ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 int BRCMF_POSTBOOT_ID ; 
 int /*<<< orphan*/  DL_GETVER ; 
 int /*<<< orphan*/  DL_RESETCFG ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_usb_dl_cmd (struct brcmf_usbdev_info*,int /*<<< orphan*/ ,struct bootrom_id_le*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
brcmf_usb_dlneeded(struct brcmf_usbdev_info *devinfo)
{
	struct bootrom_id_le id;
	u32 chipid, chiprev;

	brcmf_dbg(USB, "Enter\n");

	if (devinfo == NULL)
		return false;

	/* Check if firmware downloaded already by querying runtime ID */
	id.chip = cpu_to_le32(0xDEAD);
	brcmf_usb_dl_cmd(devinfo, DL_GETVER, &id, sizeof(id));

	chipid = le32_to_cpu(id.chip);
	chiprev = le32_to_cpu(id.chiprev);

	if ((chipid & 0x4300) == 0x4300)
		brcmf_dbg(USB, "chip %x rev 0x%x\n", chipid, chiprev);
	else
		brcmf_dbg(USB, "chip %d rev 0x%x\n", chipid, chiprev);
	if (chipid == BRCMF_POSTBOOT_ID) {
		brcmf_dbg(USB, "firmware already downloaded\n");
		brcmf_usb_dl_cmd(devinfo, DL_RESETCFG, &id, sizeof(id));
		return false;
	} else {
		devinfo->bus_pub.devid = chipid;
		devinfo->bus_pub.chiprev = chiprev;
	}
	return true;
}