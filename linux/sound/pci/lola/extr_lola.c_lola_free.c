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
struct TYPE_4__ {scalar_t__ area; } ;
struct lola {scalar_t__ irq; int /*<<< orphan*/  pci; TYPE_2__ rb; TYPE_1__* bar; scalar_t__ initialized; } ;
struct TYPE_3__ {int /*<<< orphan*/  remap_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lola*) ; 
 int /*<<< orphan*/  lola_free_mixer (struct lola*) ; 
 int /*<<< orphan*/  lola_free_pcm (struct lola*) ; 
 int /*<<< orphan*/  lola_stop_hw (struct lola*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_2__*) ; 

__attribute__((used)) static void lola_free(struct lola *chip)
{
	if (chip->initialized)
		lola_stop_hw(chip);
	lola_free_pcm(chip);
	lola_free_mixer(chip);
	if (chip->irq >= 0)
		free_irq(chip->irq, (void *)chip);
	iounmap(chip->bar[0].remap_addr);
	iounmap(chip->bar[1].remap_addr);
	if (chip->rb.area)
		snd_dma_free_pages(&chip->rb);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kfree(chip);
}