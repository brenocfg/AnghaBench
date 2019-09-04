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
 int ARRAY_SIZE (unsigned short*) ; 
 int /*<<< orphan*/  se200pci_WM8776_set_afl (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se200pci_WM8776_set_agc (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se200pci_WM8776_set_input_selector (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se200pci_WM8776_set_input_volume (struct snd_ice1712*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se200pci_WM8776_set_output_volume (struct snd_ice1712*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se200pci_WM8776_write (struct snd_ice1712*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void se200pci_WM8776_init(struct snd_ice1712 *ice)
{
	int i;
	static unsigned short default_values[] = {
		0x100, 0x100, 0x100,
		0x100, 0x100, 0x100,
		0x000, 0x090, 0x000, 0x000,
		0x022, 0x022, 0x022,
		0x008, 0x0cf, 0x0cf, 0x07b, 0x000,
		0x032, 0x000, 0x0a6, 0x001, 0x001
	};

	se200pci_WM8776_write(ice, 0x17, 0x000); /* reset all */
	/* ADC and DAC interface is I2S 24bits mode */
 	/* The sample-rate are automatically changed */
	udelay(10);
	/* BUT my board can not do reset all, so I load all by manually. */
	for (i = 0; i < ARRAY_SIZE(default_values); i++)
		se200pci_WM8776_write(ice, i, default_values[i]);

	se200pci_WM8776_set_input_selector(ice, 0);
	se200pci_WM8776_set_afl(ice, 0);
	se200pci_WM8776_set_agc(ice, 0);
	se200pci_WM8776_set_input_volume(ice, 0, 0);
	se200pci_WM8776_set_output_volume(ice, 0, 0);

	/* head phone mute and power down */
	se200pci_WM8776_write(ice, 0x00, 0);
	se200pci_WM8776_write(ice, 0x01, 0);
	se200pci_WM8776_write(ice, 0x02, 0x100);
	se200pci_WM8776_write(ice, 0x0d, 0x080);
}