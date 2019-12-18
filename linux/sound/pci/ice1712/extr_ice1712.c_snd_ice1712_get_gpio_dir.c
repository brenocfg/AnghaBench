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
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DIRECTION ; 
 unsigned int snd_ice1712_read (struct snd_ice1712*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int snd_ice1712_get_gpio_dir(struct snd_ice1712 *ice)
{
	return snd_ice1712_read(ice, ICE1712_IREG_GPIO_DIRECTION);
}