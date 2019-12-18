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
struct snd_pci_quirk {int value; int /*<<< orphan*/  subdevice; int /*<<< orphan*/  subvendor; } ;
struct azx {scalar_t__ driver_type; int driver_caps; TYPE_1__* card; int /*<<< orphan*/  pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AZX_DCAPS_AMD_WORKAROUND ; 
 int AZX_DCAPS_POSFIX_LPIB ; 
 scalar_t__ AZX_DRIVER_SKL ; 
 scalar_t__ AZX_DRIVER_VIA ; 
#define  POS_FIX_AUTO 134 
#define  POS_FIX_COMBO 133 
#define  POS_FIX_FIFO 132 
#define  POS_FIX_LPIB 131 
#define  POS_FIX_POSBUF 130 
#define  POS_FIX_SKL 129 
#define  POS_FIX_VIACOMBO 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  position_fix_list ; 
 struct snd_pci_quirk* snd_pci_quirk_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_position_fix(struct azx *chip, int fix)
{
	const struct snd_pci_quirk *q;

	switch (fix) {
	case POS_FIX_AUTO:
	case POS_FIX_LPIB:
	case POS_FIX_POSBUF:
	case POS_FIX_VIACOMBO:
	case POS_FIX_COMBO:
	case POS_FIX_SKL:
	case POS_FIX_FIFO:
		return fix;
	}

	q = snd_pci_quirk_lookup(chip->pci, position_fix_list);
	if (q) {
		dev_info(chip->card->dev,
			 "position_fix set to %d for device %04x:%04x\n",
			 q->value, q->subvendor, q->subdevice);
		return q->value;
	}

	/* Check VIA/ATI HD Audio Controller exist */
	if (chip->driver_type == AZX_DRIVER_VIA) {
		dev_dbg(chip->card->dev, "Using VIACOMBO position fix\n");
		return POS_FIX_VIACOMBO;
	}
	if (chip->driver_caps & AZX_DCAPS_AMD_WORKAROUND) {
		dev_dbg(chip->card->dev, "Using FIFO position fix\n");
		return POS_FIX_FIFO;
	}
	if (chip->driver_caps & AZX_DCAPS_POSFIX_LPIB) {
		dev_dbg(chip->card->dev, "Using LPIB position fix\n");
		return POS_FIX_LPIB;
	}
	if (chip->driver_type == AZX_DRIVER_SKL) {
		dev_dbg(chip->card->dev, "Using SKL position fix\n");
		return POS_FIX_SKL;
	}
	return POS_FIX_AUTO;
}