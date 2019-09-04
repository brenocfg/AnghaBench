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
struct rdl_state_le {scalar_t__ state; } ;
struct TYPE_2__ {int devid; } ;
struct brcmf_usbdev_info {TYPE_1__ bus_pub; } ;
typedef  int /*<<< orphan*/  state ;

/* Variables and functions */
 int /*<<< orphan*/  DL_GETSTATE ; 
 int /*<<< orphan*/  DL_GO ; 
 int /*<<< orphan*/  DL_RUNNABLE ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 scalar_t__ brcmf_usb_dl_cmd (struct brcmf_usbdev_info*,int /*<<< orphan*/ ,struct rdl_state_le*,int) ; 
 scalar_t__ brcmf_usb_resetcfg (struct brcmf_usbdev_info*) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_usb_dlrun(struct brcmf_usbdev_info *devinfo)
{
	struct rdl_state_le state;

	brcmf_dbg(USB, "Enter\n");
	if (!devinfo)
		return -EINVAL;

	if (devinfo->bus_pub.devid == 0xDEAD)
		return -EINVAL;

	/* Check we are runnable */
	state.state = 0;
	brcmf_usb_dl_cmd(devinfo, DL_GETSTATE, &state, sizeof(state));

	/* Start the image */
	if (state.state == cpu_to_le32(DL_RUNNABLE)) {
		if (brcmf_usb_dl_cmd(devinfo, DL_GO, &state, sizeof(state)))
			return -ENODEV;
		if (brcmf_usb_resetcfg(devinfo))
			return -ENODEV;
		/* The Dongle may go for re-enumeration. */
	} else {
		brcmf_err("Dongle not runnable\n");
		return -EINVAL;
	}
	brcmf_dbg(USB, "Exit\n");
	return 0;
}