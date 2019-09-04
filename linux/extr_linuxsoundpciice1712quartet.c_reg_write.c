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
struct TYPE_2__ {unsigned int (* get_data ) (struct snd_ice1712*) ;int /*<<< orphan*/  (* set_dir ) (struct snd_ice1712*,int) ;int /*<<< orphan*/  (* set_mask ) (struct snd_ice1712*,int) ;int /*<<< orphan*/  (* set_data ) (struct snd_ice1712*,unsigned int) ;} ;
struct snd_ice1712 {int /*<<< orphan*/  gpio_mutex; TYPE_1__ gpio; } ;

/* Variables and functions */
 unsigned int GPIO_DATA_MASK ; 
 unsigned int GPIO_EX_GPIOE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  stub10 (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  stub2 (struct snd_ice1712*,unsigned int) ; 
 unsigned int stub3 (struct snd_ice1712*) ; 
 int /*<<< orphan*/  stub4 (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  stub5 (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  stub6 (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  stub7 (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  stub8 (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  stub9 (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void reg_write(struct snd_ice1712 *ice, unsigned int reg,
		unsigned int data)
{
	unsigned int tmp;

	mutex_lock(&ice->gpio_mutex);
	/* set direction of used GPIOs*/
	/* all outputs */
	tmp = 0x00ffff;
	ice->gpio.set_dir(ice, tmp);
	/* mask - writable bits */
	ice->gpio.set_mask(ice, ~(tmp));
	/* write the data */
	tmp = ice->gpio.get_data(ice);
	tmp &= ~GPIO_DATA_MASK;
	tmp |= data;
	ice->gpio.set_data(ice, tmp);
	udelay(100);
	/* drop output enable */
	tmp &=  ~GPIO_EX_GPIOE;
	ice->gpio.set_data(ice, tmp);
	udelay(100);
	/* drop the register gpio */
	tmp &= ~reg;
	ice->gpio.set_data(ice, tmp);
	udelay(100);
	/* raise the register GPIO */
	tmp |= reg;
	ice->gpio.set_data(ice, tmp);
	udelay(100);

	/* raise all data gpios */
	tmp |= GPIO_DATA_MASK;
	ice->gpio.set_data(ice, tmp);
	/* mask - immutable bits */
	ice->gpio.set_mask(ice, 0xffffff);
	/* outputs only 8-15 */
	ice->gpio.set_dir(ice, 0x00ff00);
	mutex_unlock(&ice->gpio_mutex);
}