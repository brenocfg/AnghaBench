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
struct tb10x_pinctrl {int /*<<< orphan*/  mutex; int /*<<< orphan*/  gpios; } ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tb10x_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static void tb10x_gpio_disable_free(struct pinctrl_dev *pctl,
					struct pinctrl_gpio_range *range,
					unsigned pin)
{
	struct tb10x_pinctrl *state = pinctrl_dev_get_drvdata(pctl);

	mutex_lock(&state->mutex);

	clear_bit(pin, state->gpios);

	mutex_unlock(&state->mutex);
}