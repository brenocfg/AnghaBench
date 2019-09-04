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
struct snd_ymfpci {scalar_t__ device_id; TYPE_2__* card; TYPE_3__* controller_microcode; TYPE_1__* pci; TYPE_3__* dsp_microcode; } ;
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PCI_DEVICE_ID_YAMAHA_724F ; 
 scalar_t__ PCI_DEVICE_ID_YAMAHA_740C ; 
 scalar_t__ PCI_DEVICE_ID_YAMAHA_744 ; 
 scalar_t__ PCI_DEVICE_ID_YAMAHA_754 ; 
 scalar_t__ YDSXG_CTRLLENGTH ; 
 scalar_t__ YDSXG_DSPLENGTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int request_firmware (TYPE_3__**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ymfpci_request_firmware(struct snd_ymfpci *chip)
{
	int err, is_1e;
	const char *name;

	err = request_firmware(&chip->dsp_microcode, "yamaha/ds1_dsp.fw",
			       &chip->pci->dev);
	if (err >= 0) {
		if (chip->dsp_microcode->size != YDSXG_DSPLENGTH) {
			dev_err(chip->card->dev,
				"DSP microcode has wrong size\n");
			err = -EINVAL;
		}
	}
	if (err < 0)
		return err;
	is_1e = chip->device_id == PCI_DEVICE_ID_YAMAHA_724F ||
		chip->device_id == PCI_DEVICE_ID_YAMAHA_740C ||
		chip->device_id == PCI_DEVICE_ID_YAMAHA_744 ||
		chip->device_id == PCI_DEVICE_ID_YAMAHA_754;
	name = is_1e ? "yamaha/ds1e_ctrl.fw" : "yamaha/ds1_ctrl.fw";
	err = request_firmware(&chip->controller_microcode, name,
			       &chip->pci->dev);
	if (err >= 0) {
		if (chip->controller_microcode->size != YDSXG_CTRLLENGTH) {
			dev_err(chip->card->dev,
				"controller microcode has wrong size\n");
			err = -EINVAL;
		}
	}
	if (err < 0)
		return err;
	return 0;
}