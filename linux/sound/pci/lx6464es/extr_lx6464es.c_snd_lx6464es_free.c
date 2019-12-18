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
struct lx6464es {scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  port_plx_remapped; int /*<<< orphan*/  port_dsp_bar; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct lx6464es*) ; 
 int /*<<< orphan*/  ioport_unmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lx6464es*) ; 
 int /*<<< orphan*/  lx_irq_disable (struct lx6464es*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_lx6464es_free(struct lx6464es *chip)
{
	dev_dbg(chip->card->dev, "->snd_lx6464es_free\n");

	lx_irq_disable(chip);

	if (chip->irq >= 0)
		free_irq(chip->irq, chip);

	iounmap(chip->port_dsp_bar);
	ioport_unmap(chip->port_plx_remapped);

	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);

	kfree(chip);

	return 0;
}