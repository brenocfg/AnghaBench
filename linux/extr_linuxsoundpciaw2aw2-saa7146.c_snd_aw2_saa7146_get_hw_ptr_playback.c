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
struct snd_aw2_saa7146 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ADP1 ; 
 int /*<<< orphan*/  PCI_ADP3 ; 
 long READREG (int /*<<< orphan*/ ) ; 

unsigned int snd_aw2_saa7146_get_hw_ptr_playback(struct snd_aw2_saa7146 *chip,
						 int stream_number,
						 unsigned char *start_addr,
						 unsigned int buffer_size)
{
	long pci_adp = 0;
	size_t ptr = 0;

	if (stream_number == 0) {
		pci_adp = READREG(PCI_ADP3);
		ptr = pci_adp - (long)start_addr;

		if (ptr == buffer_size)
			ptr = 0;
	}
	if (stream_number == 1) {
		pci_adp = READREG(PCI_ADP1);
		ptr = pci_adp - (size_t) start_addr;

		if (ptr == buffer_size)
			ptr = 0;
	}
	return ptr;
}