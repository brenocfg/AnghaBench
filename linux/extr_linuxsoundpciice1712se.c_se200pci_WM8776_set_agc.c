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
 int /*<<< orphan*/  se200pci_WM8776_write (struct snd_ice1712*,int,int) ; 

__attribute__((used)) static void se200pci_WM8776_set_agc(struct snd_ice1712 *ice, unsigned int agc)
{
	/* AGC -- Auto Gain Control of the input */
	switch (agc) {
	case 0:
		se200pci_WM8776_write(ice, 0x11, 0x000); /* Off */
		break;
	case 1:
		se200pci_WM8776_write(ice, 0x10, 0x07b);
		se200pci_WM8776_write(ice, 0x11, 0x100); /* LimiterMode */
		break;
	case 2:
		se200pci_WM8776_write(ice, 0x10, 0x1fb);
		se200pci_WM8776_write(ice, 0x11, 0x100); /* ALCMode */
		break;
	}
}