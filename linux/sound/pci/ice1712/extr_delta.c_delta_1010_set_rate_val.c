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
 unsigned char ICE1712_DELTA_DFS ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DATA ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned char snd_ice1712_read (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ice1712_write (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void delta_1010_set_rate_val(struct snd_ice1712 *ice, unsigned int rate)
{
	unsigned char tmp, tmp2;

	if (rate == 0)	/* no hint - S/PDIF input is master, simply return */
		return;

	mutex_lock(&ice->gpio_mutex);
	tmp = snd_ice1712_read(ice, ICE1712_IREG_GPIO_DATA);
	tmp2 = tmp & ~ICE1712_DELTA_DFS;
	if (rate > 48000)
		tmp2 |= ICE1712_DELTA_DFS;
	if (tmp != tmp2)
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA, tmp2);
	mutex_unlock(&ice->gpio_mutex);
}