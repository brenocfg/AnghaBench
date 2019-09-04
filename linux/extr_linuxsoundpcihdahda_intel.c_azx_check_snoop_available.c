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
typedef  int u8 ;
struct azx {int snoop; int uc_buffer; scalar_t__ driver_type; int driver_caps; TYPE_1__* card; TYPE_2__* pci; } ;
struct TYPE_4__ {int revision; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AZX_DCAPS_SNOOP_OFF ; 
 scalar_t__ AZX_DRIVER_CMEDIA ; 
 scalar_t__ AZX_DRIVER_VIA ; 
 scalar_t__ AZX_SNOOP_TYPE_NONE ; 
 scalar_t__ azx_get_snoop_type (struct azx*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int hda_snoop ; 
 int /*<<< orphan*/  pci_read_config_byte (TYPE_2__*,int,int*) ; 

__attribute__((used)) static void azx_check_snoop_available(struct azx *chip)
{
	int snoop = hda_snoop;

	if (snoop >= 0) {
		dev_info(chip->card->dev, "Force to %s mode by module option\n",
			 snoop ? "snoop" : "non-snoop");
		chip->snoop = snoop;
		chip->uc_buffer = !snoop;
		return;
	}

	snoop = true;
	if (azx_get_snoop_type(chip) == AZX_SNOOP_TYPE_NONE &&
	    chip->driver_type == AZX_DRIVER_VIA) {
		/* force to non-snoop mode for a new VIA controller
		 * when BIOS is set
		 */
		u8 val;
		pci_read_config_byte(chip->pci, 0x42, &val);
		if (!(val & 0x80) && (chip->pci->revision == 0x30 ||
				      chip->pci->revision == 0x20))
			snoop = false;
	}

	if (chip->driver_caps & AZX_DCAPS_SNOOP_OFF)
		snoop = false;

	chip->snoop = snoop;
	if (!snoop) {
		dev_info(chip->card->dev, "Force to non-snoop mode\n");
		/* C-Media requires non-cached pages only for CORB/RIRB */
		if (chip->driver_type != AZX_DRIVER_CMEDIA)
			chip->uc_buffer = true;
	}
}