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
 unsigned int PHASE28_SPI_CLK ; 
 unsigned int PHASE28_SPI_MOSI ; 
 unsigned int PHASE28_WM_CS ; 
 unsigned int PHASE28_WM_RW ; 
 unsigned int snd_ice1712_gpio_read (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_mask (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_write (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void phase28_spi_write(struct snd_ice1712 *ice, unsigned int cs,
				unsigned int data, int bits)
{
	unsigned int tmp;
	int i;

	tmp = snd_ice1712_gpio_read(ice);

	snd_ice1712_gpio_set_mask(ice, ~(PHASE28_WM_RW|PHASE28_SPI_MOSI|
					PHASE28_SPI_CLK|PHASE28_WM_CS));
	tmp |= PHASE28_WM_RW;
	tmp &= ~cs;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(1);

	for (i = bits - 1; i >= 0; i--) {
		tmp &= ~PHASE28_SPI_CLK;
		snd_ice1712_gpio_write(ice, tmp);
		udelay(1);
		if (data & (1 << i))
			tmp |= PHASE28_SPI_MOSI;
		else
			tmp &= ~PHASE28_SPI_MOSI;
		snd_ice1712_gpio_write(ice, tmp);
		udelay(1);
		tmp |= PHASE28_SPI_CLK;
		snd_ice1712_gpio_write(ice, tmp);
		udelay(1);
	}

	tmp &= ~PHASE28_SPI_CLK;
	tmp |= cs;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(1);
	tmp |= PHASE28_SPI_CLK;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(1);
}