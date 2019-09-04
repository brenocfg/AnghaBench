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
struct hdsp {int control_register; scalar_t__ irq; int /*<<< orphan*/  pci; scalar_t__ port; int /*<<< orphan*/  iobase; int /*<<< orphan*/  fw_uploaded; int /*<<< orphan*/  firmware; int /*<<< orphan*/  midi_tasklet; } ;

/* Variables and functions */
 int HDSP_AudioInterruptEnable ; 
 int HDSP_Midi0InterruptEnable ; 
 int HDSP_Midi1InterruptEnable ; 
 int HDSP_Start ; 
 int /*<<< orphan*/  HDSP_controlRegister ; 
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdsp_free_buffers (struct hdsp*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_hdsp_free(struct hdsp *hdsp)
{
	if (hdsp->port) {
		/* stop the audio, and cancel all interrupts */
		tasklet_kill(&hdsp->midi_tasklet);
		hdsp->control_register &= ~(HDSP_Start|HDSP_AudioInterruptEnable|HDSP_Midi0InterruptEnable|HDSP_Midi1InterruptEnable);
		hdsp_write (hdsp, HDSP_controlRegister, hdsp->control_register);
	}

	if (hdsp->irq >= 0)
		free_irq(hdsp->irq, (void *)hdsp);

	snd_hdsp_free_buffers(hdsp);

	release_firmware(hdsp->firmware);
	vfree(hdsp->fw_uploaded);
	iounmap(hdsp->iobase);

	if (hdsp->port)
		pci_release_regions(hdsp->pci);

	pci_disable_device(hdsp->pci);
	return 0;
}