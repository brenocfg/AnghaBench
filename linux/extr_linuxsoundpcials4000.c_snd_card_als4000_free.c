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
struct snd_card_als4000 {int /*<<< orphan*/  pci; int /*<<< orphan*/  iobase; } ;
struct snd_card {struct snd_card_als4000* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALS4K_GCR8C_MISC_CTRL ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_als4000_free_gameport (struct snd_card_als4000*) ; 
 int /*<<< orphan*/  snd_als4k_gcr_write_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_card_als4000_free( struct snd_card *card )
{
	struct snd_card_als4000 *acard = card->private_data;

	/* make sure that interrupts are disabled */
	snd_als4k_gcr_write_addr(acard->iobase, ALS4K_GCR8C_MISC_CTRL, 0);
	/* free resources */
	snd_als4000_free_gameport(acard);
	pci_release_regions(acard->pci);
	pci_disable_device(acard->pci);
}