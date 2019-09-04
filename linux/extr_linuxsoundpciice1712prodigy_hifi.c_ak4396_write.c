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
 int AK4396_ADDR ; 
 int AK4396_CCLK ; 
 int AK4396_CDTI ; 
 int AK4396_CSN ; 
 int /*<<< orphan*/  ak4396_send_word (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  set_gpio_bit (struct snd_ice1712*,int,int) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_dir (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_mask (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ak4396_write(struct snd_ice1712 *ice, unsigned int reg,
			 unsigned int data)
{
	unsigned int block;

	snd_ice1712_gpio_set_dir(ice, AK4396_CSN|AK4396_CCLK|AK4396_CDTI);
	snd_ice1712_gpio_set_mask(ice, ~(AK4396_CSN|AK4396_CCLK|AK4396_CDTI));
	/* latch must be low when writing */
	set_gpio_bit(ice, AK4396_CSN, 0); 
	block =  ((AK4396_ADDR & 0x03) << 14) | (1 << 13) |
			((reg & 0x1f) << 8) | (data & 0xff);
	ak4396_send_word(ice, block); /* REGISTER ADDRESS */
	/* release latch */
	set_gpio_bit(ice, AK4396_CSN, 1);
	udelay(1);
	/* restore */
	snd_ice1712_gpio_set_mask(ice, ice->gpio.write_mask);
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction);
}