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
struct hdspm {int control_register; scalar_t__ irq; int /*<<< orphan*/  pci; scalar_t__ port; int /*<<< orphan*/  iobase; int /*<<< orphan*/  mixer; } ;

/* Variables and functions */
 int HDSPM_AudioInterruptEnable ; 
 int HDSPM_Midi0InterruptEnable ; 
 int HDSPM_Midi1InterruptEnable ; 
 int HDSPM_Midi2InterruptEnable ; 
 int HDSPM_Midi3InterruptEnable ; 
 int HDSPM_Start ; 
 int /*<<< orphan*/  HDSPM_controlRegister ; 
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_hdspm_free(struct hdspm * hdspm)
{

	if (hdspm->port) {

		/* stop th audio, and cancel all interrupts */
		hdspm->control_register &=
		    ~(HDSPM_Start | HDSPM_AudioInterruptEnable |
		      HDSPM_Midi0InterruptEnable | HDSPM_Midi1InterruptEnable |
		      HDSPM_Midi2InterruptEnable | HDSPM_Midi3InterruptEnable);
		hdspm_write(hdspm, HDSPM_controlRegister,
			    hdspm->control_register);
	}

	if (hdspm->irq >= 0)
		free_irq(hdspm->irq, (void *) hdspm);

	kfree(hdspm->mixer);
	iounmap(hdspm->iobase);

	if (hdspm->port)
		pci_release_regions(hdspm->pci);

	pci_disable_device(hdspm->pci);
	return 0;
}