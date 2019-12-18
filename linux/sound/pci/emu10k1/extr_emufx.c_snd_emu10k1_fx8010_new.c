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
struct TYPE_2__ {int /*<<< orphan*/  release; int /*<<< orphan*/  ioctl; int /*<<< orphan*/  open; } ;
struct snd_hwdep {struct snd_emu10k1* private_data; TYPE_1__ ops; int /*<<< orphan*/  iface; int /*<<< orphan*/  name; } ;
struct snd_emu10k1 {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_HWDEP_IFACE_EMU10K1 ; 
 int /*<<< orphan*/  snd_emu10k1_fx8010_ioctl ; 
 int /*<<< orphan*/  snd_emu10k1_fx8010_open ; 
 int /*<<< orphan*/  snd_emu10k1_fx8010_release ; 
 int snd_hwdep_new (int /*<<< orphan*/ ,char*,int,struct snd_hwdep**) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int snd_emu10k1_fx8010_new(struct snd_emu10k1 *emu, int device)
{
	struct snd_hwdep *hw;
	int err;
	
	if ((err = snd_hwdep_new(emu->card, "FX8010", device, &hw)) < 0)
		return err;
	strcpy(hw->name, "EMU10K1 (FX8010)");
	hw->iface = SNDRV_HWDEP_IFACE_EMU10K1;
	hw->ops.open = snd_emu10k1_fx8010_open;
	hw->ops.ioctl = snd_emu10k1_fx8010_ioctl;
	hw->ops.release = snd_emu10k1_fx8010_release;
	hw->private_data = emu;
	return 0;
}