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
struct snd_rme9652 {scalar_t__ irq; int /*<<< orphan*/  pci; scalar_t__ port; int /*<<< orphan*/  iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rme9652_stop (struct snd_rme9652*) ; 
 int /*<<< orphan*/  snd_rme9652_free_buffers (struct snd_rme9652*) ; 

__attribute__((used)) static int snd_rme9652_free(struct snd_rme9652 *rme9652)
{
	if (rme9652->irq >= 0)
		rme9652_stop(rme9652);
	snd_rme9652_free_buffers(rme9652);

	if (rme9652->irq >= 0)
		free_irq(rme9652->irq, (void *)rme9652);
	iounmap(rme9652->iobase);
	if (rme9652->port)
		pci_release_regions(rme9652->pci);

	pci_disable_device(rme9652->pci);
	return 0;
}