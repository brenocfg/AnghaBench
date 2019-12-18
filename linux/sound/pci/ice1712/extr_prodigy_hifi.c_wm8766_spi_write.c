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
struct TYPE_2__ {int write_mask; int direction; } ;
struct snd_ice1712 {TYPE_1__ gpio; } ;

/* Variables and functions */
 int WM8766_SPI_CLK ; 
 int WM8766_SPI_MD ; 
 int WM8766_SPI_ML ; 
 int /*<<< orphan*/  set_gpio_bit (struct snd_ice1712*,int,int) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_dir (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_mask (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wm8766_spi_send_word (struct snd_ice1712*,unsigned int) ; 

__attribute__((used)) static void wm8766_spi_write(struct snd_ice1712 *ice, unsigned int reg,
			     unsigned int data)
{
	unsigned int block;

	snd_ice1712_gpio_set_dir(ice, WM8766_SPI_MD|
					WM8766_SPI_CLK|WM8766_SPI_ML);
	snd_ice1712_gpio_set_mask(ice, ~(WM8766_SPI_MD|
					WM8766_SPI_CLK|WM8766_SPI_ML));
	/* latch must be low when writing */
	set_gpio_bit(ice, WM8766_SPI_ML, 0);
	block = (reg << 9) | (data & 0x1ff);
	wm8766_spi_send_word(ice, block); /* REGISTER ADDRESS */
	/* release latch */
	set_gpio_bit(ice, WM8766_SPI_ML, 1);
	udelay(1);
	/* restore */
	snd_ice1712_gpio_set_mask(ice, ice->gpio.write_mask);
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction);
}