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
struct TYPE_2__ {int /*<<< orphan*/ * saved; int /*<<< orphan*/  write_mask; int /*<<< orphan*/  direction; int /*<<< orphan*/  (* set_mask ) (struct snd_ice1712*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_dir ) (struct snd_ice1712*,int /*<<< orphan*/ ) ;} ;
struct snd_ice1712 {int /*<<< orphan*/  gpio_mutex; TYPE_1__ gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void snd_ice1712_restore_gpio_status(struct snd_ice1712 *ice)
{
	ice->gpio.set_dir(ice, ice->gpio.saved[0]);
	ice->gpio.set_mask(ice, ice->gpio.saved[1]);
	ice->gpio.direction = ice->gpio.saved[0];
	ice->gpio.write_mask = ice->gpio.saved[1];
	mutex_unlock(&ice->gpio_mutex);
}