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
 unsigned int AUREON_HP_SEL ; 
 unsigned int snd_ice1712_gpio_read (struct snd_ice1712*) ; 

__attribute__((used)) static int aureon_get_headphone_amp(struct snd_ice1712 *ice)
{
	unsigned int tmp = snd_ice1712_gpio_read(ice);

	return (tmp & AUREON_HP_SEL) != 0;
}