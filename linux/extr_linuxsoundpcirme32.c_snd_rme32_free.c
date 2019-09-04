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
struct rme32 {int irq; int /*<<< orphan*/  pci; scalar_t__ port; int /*<<< orphan*/ * iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,void*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rme32_pcm_stop (struct rme32*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_rme32_free(void *private_data)
{
	struct rme32 *rme32 = (struct rme32 *) private_data;

	if (rme32 == NULL) {
		return;
	}
	if (rme32->irq >= 0) {
		snd_rme32_pcm_stop(rme32, 0);
		free_irq(rme32->irq, (void *) rme32);
		rme32->irq = -1;
	}
	if (rme32->iobase) {
		iounmap(rme32->iobase);
		rme32->iobase = NULL;
	}
	if (rme32->port) {
		pci_release_regions(rme32->pci);
		rme32->port = 0;
	}
	pci_disable_device(rme32->pci);
}