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
struct nxp_74hc153_platform_data {unsigned int gpio_pin_2y; unsigned int gpio_pin_1y; int /*<<< orphan*/  gpio_pin_s1; int /*<<< orphan*/  gpio_pin_s0; } ;
struct nxp_74hc153_chip {int /*<<< orphan*/  lock; TYPE_1__* parent; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {struct nxp_74hc153_platform_data* platform_data; } ;

/* Variables and functions */
 unsigned int NXP_74HC153_BANK_MASK ; 
 unsigned int NXP_74HC153_S0_MASK ; 
 unsigned int NXP_74HC153_S1_MASK ; 
 int gpio_get_value (unsigned int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,unsigned int) ; 
 struct nxp_74hc153_chip* gpio_to_nxp (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nxp_74hc153_get_value(struct gpio_chip *gc, unsigned offset)
{
	struct nxp_74hc153_chip *nxp;
	struct nxp_74hc153_platform_data *pdata;
	unsigned s0;
	unsigned s1;
	unsigned pin;
	int ret;

	nxp = gpio_to_nxp(gc);
	pdata = nxp->parent->platform_data;

	s0 = !!(offset & NXP_74HC153_S0_MASK);
	s1 = !!(offset & NXP_74HC153_S1_MASK);
	pin = (offset & NXP_74HC153_BANK_MASK) ? pdata->gpio_pin_2y
					       : pdata->gpio_pin_1y;

	mutex_lock(&nxp->lock);
	gpio_set_value(pdata->gpio_pin_s0, s0);
	gpio_set_value(pdata->gpio_pin_s1, s1);
	ret = gpio_get_value(pin);
	mutex_unlock(&nxp->lock);

	return ret;
}