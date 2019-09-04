#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int const direction; unsigned int const write_mask; } ;
struct snd_ice1712 {TYPE_1__ gpio; } ;

/* Variables and functions */
 unsigned int const snd_ice1712_gpio_read (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_dir (struct snd_ice1712*,unsigned int const) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_mask (struct snd_ice1712*,unsigned int const) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_write (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  snd_ice1712_restore_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void se200pci_WM8766_write(struct snd_ice1712 *ice,
					unsigned int addr, unsigned int data)
{
	unsigned int st;
	unsigned int bits;
	int i;
	const unsigned int DATA  = 0x010000;
	const unsigned int CLOCK = 0x020000;
	const unsigned int LOAD  = 0x040000;
	const unsigned int ALL_MASK = (DATA | CLOCK | LOAD);

	snd_ice1712_save_gpio_status(ice);

	st = ((addr & 0x7f) << 9) | (data & 0x1ff);
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction | ALL_MASK);
	snd_ice1712_gpio_set_mask(ice, ice->gpio.write_mask & ~ALL_MASK);
	bits = snd_ice1712_gpio_read(ice) & ~ALL_MASK;

	snd_ice1712_gpio_write(ice, bits);
	for (i = 0; i < 16; i++) {
		udelay(1);
		bits &= ~CLOCK;
		st = (st << 1);
		if (st & 0x10000)
			bits |= DATA;
		else
			bits &= ~DATA;

		snd_ice1712_gpio_write(ice, bits);

		udelay(1);
		bits |= CLOCK;
		snd_ice1712_gpio_write(ice, bits);
	}

	udelay(1);
	bits |= LOAD;
	snd_ice1712_gpio_write(ice, bits);

	udelay(1);
	bits |= (DATA | CLOCK);
	snd_ice1712_gpio_write(ice, bits);

	snd_ice1712_restore_gpio_status(ice);
}