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
struct TYPE_4__ {int use_posbuf; int corbrp_self_clear; int align_bdle_4k; int sync_write; int /*<<< orphan*/  bdl_pos_adj; int /*<<< orphan*/  snoop; } ;
struct hda_bus {char const* modelname; int mixer_assigned; int allow_bus_reset; TYPE_2__ core; int /*<<< orphan*/  pci; int /*<<< orphan*/  prepare_mutex; TYPE_1__* card; } ;
struct azx {scalar_t__* get_position; int driver_caps; TYPE_1__* card; int /*<<< orphan*/  bdl_pos_adj; int /*<<< orphan*/  pci; struct hda_bus bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AZX_DCAPS_4K_BDLE_BOUNDARY ; 
 int AZX_DCAPS_CORBRP_SELF_CLEAR ; 
 int AZX_DCAPS_SYNC_WRITE ; 
 scalar_t__ azx_get_pos_lpib ; 
 int /*<<< orphan*/  azx_snoop (struct azx*) ; 
 int /*<<< orphan*/  bus_core_ops ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_hdac_bus_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int azx_bus_init(struct azx *chip, const char *model)
{
	struct hda_bus *bus = &chip->bus;
	int err;

	err = snd_hdac_bus_init(&bus->core, chip->card->dev, &bus_core_ops);
	if (err < 0)
		return err;

	bus->card = chip->card;
	mutex_init(&bus->prepare_mutex);
	bus->pci = chip->pci;
	bus->modelname = model;
	bus->mixer_assigned = -1;
	bus->core.snoop = azx_snoop(chip);
	if (chip->get_position[0] != azx_get_pos_lpib ||
	    chip->get_position[1] != azx_get_pos_lpib)
		bus->core.use_posbuf = true;
	bus->core.bdl_pos_adj = chip->bdl_pos_adj;
	if (chip->driver_caps & AZX_DCAPS_CORBRP_SELF_CLEAR)
		bus->core.corbrp_self_clear = true;

	if (chip->driver_caps & AZX_DCAPS_4K_BDLE_BOUNDARY)
		bus->core.align_bdle_4k = true;

	/* AMD chipsets often cause the communication stalls upon certain
	 * sequence like the pin-detection.  It seems that forcing the synced
	 * access works around the stall.  Grrr...
	 */
	if (chip->driver_caps & AZX_DCAPS_SYNC_WRITE) {
		dev_dbg(chip->card->dev, "Enable sync_write for stable communication\n");
		bus->core.sync_write = 1;
		bus->allow_bus_reset = 1;
	}

	return 0;
}