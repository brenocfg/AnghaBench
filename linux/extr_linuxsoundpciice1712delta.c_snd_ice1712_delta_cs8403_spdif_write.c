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
struct snd_ice1712 {int /*<<< orphan*/  gpio_mutex; } ;

/* Variables and functions */
 unsigned char ICE1712_DELTA_SPDIF_OUT_STAT_CLOCK ; 
 unsigned char ICE1712_DELTA_SPDIF_OUT_STAT_DATA ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DATA ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned char snd_ice1712_read (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ice1712_write (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_ice1712_delta_cs8403_spdif_write(struct snd_ice1712 *ice, unsigned char bits)
{
	unsigned char tmp, mask1, mask2;
	int idx;
	/* send byte to transmitter */
	mask1 = ICE1712_DELTA_SPDIF_OUT_STAT_CLOCK;
	mask2 = ICE1712_DELTA_SPDIF_OUT_STAT_DATA;
	mutex_lock(&ice->gpio_mutex);
	tmp = snd_ice1712_read(ice, ICE1712_IREG_GPIO_DATA);
	for (idx = 7; idx >= 0; idx--) {
		tmp &= ~(mask1 | mask2);
		if (bits & (1 << idx))
			tmp |= mask2;
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA, tmp);
		udelay(100);
		tmp |= mask1;
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA, tmp);
		udelay(100);
	}
	tmp &= ~mask1;
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA, tmp);
	mutex_unlock(&ice->gpio_mutex);
}