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
struct snd_i2c_bus {struct snd_ice1712* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 

__attribute__((used)) static void revo_i2c_start(struct snd_i2c_bus *bus)
{
	struct snd_ice1712 *ice = bus->private_data;
	snd_ice1712_save_gpio_status(ice);
}