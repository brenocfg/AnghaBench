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
 int /*<<< orphan*/  se200pci_WM8766_write (struct snd_ice1712*,int,unsigned int) ; 

__attribute__((used)) static void se200pci_WM8766_set_volume(struct snd_ice1712 *ice, int ch,
					unsigned int vol1, unsigned int vol2)
{
	switch (ch) {
	case 0:
		se200pci_WM8766_write(ice, 0x000, vol1);
		se200pci_WM8766_write(ice, 0x001, vol2 | 0x100);
		break;
	case 1:
		se200pci_WM8766_write(ice, 0x004, vol1);
		se200pci_WM8766_write(ice, 0x005, vol2 | 0x100);
		break;
	case 2:
		se200pci_WM8766_write(ice, 0x006, vol1);
		se200pci_WM8766_write(ice, 0x007, vol2 | 0x100);
		break;
	}
}