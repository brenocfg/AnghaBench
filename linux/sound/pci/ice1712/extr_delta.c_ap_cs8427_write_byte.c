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
 unsigned char ICE1712_DELTA_AP_CCLK ; 
 unsigned char ICE1712_DELTA_AP_DOUT ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DATA ; 
 int /*<<< orphan*/  snd_ice1712_write (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ap_cs8427_write_byte(struct snd_ice1712 *ice, unsigned char data, unsigned char tmp)
{
	int idx;

	for (idx = 7; idx >= 0; idx--) {
		tmp &= ~(ICE1712_DELTA_AP_DOUT|ICE1712_DELTA_AP_CCLK);
		if (data & (1 << idx))
			tmp |= ICE1712_DELTA_AP_DOUT;
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA, tmp);
		udelay(5);
		tmp |= ICE1712_DELTA_AP_CCLK;
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA, tmp);
		udelay(5);
	}
}