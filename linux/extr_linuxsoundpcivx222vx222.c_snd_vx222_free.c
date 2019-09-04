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
struct vx_core {scalar_t__ irq; } ;
struct snd_vx222 {int /*<<< orphan*/  pci; scalar_t__* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  kfree (struct vx_core*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 struct snd_vx222* to_vx222 (struct vx_core*) ; 

__attribute__((used)) static int snd_vx222_free(struct vx_core *chip)
{
	struct snd_vx222 *vx = to_vx222(chip);

	if (chip->irq >= 0)
		free_irq(chip->irq, (void*)chip);
	if (vx->port[0])
		pci_release_regions(vx->pci);
	pci_disable_device(vx->pci);
	kfree(chip);
	return 0;
}