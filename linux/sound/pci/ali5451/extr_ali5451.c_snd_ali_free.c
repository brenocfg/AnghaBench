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
struct snd_ali {scalar_t__ irq; int /*<<< orphan*/  pci_m7101; int /*<<< orphan*/  pci_m1533; struct snd_ali* image; int /*<<< orphan*/  pci; scalar_t__ port; scalar_t__ hw_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_ali*) ; 
 int /*<<< orphan*/  kfree (struct snd_ali*) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ali_disable_address_interrupt (struct snd_ali*) ; 

__attribute__((used)) static int snd_ali_free(struct snd_ali * codec)
{
	if (codec->hw_initialized)
		snd_ali_disable_address_interrupt(codec);
	if (codec->irq >= 0)
		free_irq(codec->irq, codec);
	if (codec->port)
		pci_release_regions(codec->pci);
	pci_disable_device(codec->pci);
#ifdef CONFIG_PM_SLEEP
	kfree(codec->image);
#endif
	pci_dev_put(codec->pci_m1533);
	pci_dev_put(codec->pci_m7101);
	kfree(codec);
	return 0;
}