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
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  se200pci_WM8776_write (struct snd_ice1712*,int,unsigned char) ; 

__attribute__((used)) static void se200pci_WM8776_set_input_selector(struct snd_ice1712 *ice,
					       unsigned int sel)
{
	static unsigned char vals[] = {
		/* LINE, CD, MIC, ALL, GND */
		0x10, 0x04, 0x08, 0x1c, 0x03
	};
	if (sel > 4)
		sel = 4;
	se200pci_WM8776_write(ice, 0x15, vals[sel]);
}