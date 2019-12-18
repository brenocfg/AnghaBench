#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_riptide {scalar_t__ irq; int /*<<< orphan*/  res_port; int /*<<< orphan*/  fw_entry; struct snd_riptide* cif; int /*<<< orphan*/  hwport; } ;
struct cmdif {scalar_t__ irq; int /*<<< orphan*/  res_port; int /*<<< orphan*/  fw_entry; struct cmdif* cif; int /*<<< orphan*/  hwport; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_GRESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNSET_GRESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_riptide*) ; 
 int /*<<< orphan*/  kfree (struct snd_riptide*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_riptide_free(struct snd_riptide *chip)
{
	struct cmdif *cif;

	if (!chip)
		return 0;

	if ((cif = chip->cif)) {
		SET_GRESET(cif->hwport);
		udelay(100);
		UNSET_GRESET(cif->hwport);
		kfree(chip->cif);
	}
	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
	release_firmware(chip->fw_entry);
	release_and_free_resource(chip->res_port);
	kfree(chip);
	return 0;
}