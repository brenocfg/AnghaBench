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
struct snd_pci_quirk {int value; int /*<<< orphan*/  subdevice; int /*<<< orphan*/  subvendor; } ;
struct azx {int codec_probe_mask; TYPE_1__* card; int /*<<< orphan*/  pci; } ;
struct TYPE_4__ {int codec_mask; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AZX_FORCE_CODEC_MASK ; 
 TYPE_2__* azx_bus (struct azx*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,...) ; 
 int* probe_mask ; 
 int /*<<< orphan*/  probe_mask_list ; 
 struct snd_pci_quirk* snd_pci_quirk_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_probe_mask(struct azx *chip, int dev)
{
	const struct snd_pci_quirk *q;

	chip->codec_probe_mask = probe_mask[dev];
	if (chip->codec_probe_mask == -1) {
		q = snd_pci_quirk_lookup(chip->pci, probe_mask_list);
		if (q) {
			dev_info(chip->card->dev,
				 "probe_mask set to 0x%x for device %04x:%04x\n",
				 q->value, q->subvendor, q->subdevice);
			chip->codec_probe_mask = q->value;
		}
	}

	/* check forced option */
	if (chip->codec_probe_mask != -1 &&
	    (chip->codec_probe_mask & AZX_FORCE_CODEC_MASK)) {
		azx_bus(chip)->codec_mask = chip->codec_probe_mask & 0xff;
		dev_info(chip->card->dev, "codec_mask forced to 0x%x\n",
			 (int)azx_bus(chip)->codec_mask);
	}
}