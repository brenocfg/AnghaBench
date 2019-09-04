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
struct snd_hwdep {struct snd_card_asihpi* private_data; TYPE_1__ ops; int /*<<< orphan*/  iface; int /*<<< orphan*/  name; } ;
struct snd_card_asihpi {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_HWDEP_IFACE_LAST ; 
 int /*<<< orphan*/  snd_asihpi_hpi_ioctl ; 
 int /*<<< orphan*/  snd_asihpi_hpi_open ; 
 int /*<<< orphan*/  snd_asihpi_hpi_release ; 
 int snd_hwdep_new (int /*<<< orphan*/ ,char*,int,struct snd_hwdep**) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_asihpi_hpi_new(struct snd_card_asihpi *asihpi, int device)
{
	struct snd_hwdep *hw;
	int err;

	err = snd_hwdep_new(asihpi->card, "HPI", device, &hw);
	if (err < 0)
		return err;
	strcpy(hw->name, "asihpi (HPI)");
	hw->iface = SNDRV_HWDEP_IFACE_LAST;
	hw->ops.open = snd_asihpi_hpi_open;
	hw->ops.ioctl = snd_asihpi_hpi_ioctl;
	hw->ops.release = snd_asihpi_hpi_release;
	hw->private_data = asihpi;
	return 0;
}