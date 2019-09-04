#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {scalar_t__ subsystem_vendor; scalar_t__ subsystem_device; int /*<<< orphan*/  dev; int /*<<< orphan*/  device; } ;
struct TYPE_3__ {scalar_t__ subvendor; scalar_t__ subdevice; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EBUSY ; 
 int SND_BT87X_BOARD_UNKNOWN ; 
 TYPE_1__* blacklist ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 struct pci_device_id* pci_match_id (int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  snd_bt87x_ids ; 

__attribute__((used)) static int snd_bt87x_detect_card(struct pci_dev *pci)
{
	int i;
	const struct pci_device_id *supported;

	supported = pci_match_id(snd_bt87x_ids, pci);
	if (supported && supported->driver_data > 0)
		return supported->driver_data;

	for (i = 0; i < ARRAY_SIZE(blacklist); ++i)
		if (blacklist[i].subvendor == pci->subsystem_vendor &&
		    blacklist[i].subdevice == pci->subsystem_device) {
			dev_dbg(&pci->dev,
				"card %#04x-%#04x:%#04x has no audio\n",
				    pci->device, pci->subsystem_vendor, pci->subsystem_device);
			return -EBUSY;
		}

	dev_info(&pci->dev, "unknown card %#04x-%#04x:%#04x\n",
		   pci->device, pci->subsystem_vendor, pci->subsystem_device);
	dev_info(&pci->dev, "please mail id, board name, and, "
		   "if it works, the correct digital_rate option to "
		   "<alsa-devel@alsa-project.org>\n");
	return SND_BT87X_BOARD_UNKNOWN;
}