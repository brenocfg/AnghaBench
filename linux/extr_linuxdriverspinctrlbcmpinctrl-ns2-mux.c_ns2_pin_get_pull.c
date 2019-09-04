#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pinctrl_dev {TYPE_2__* desc; } ;
struct ns2_pinctrl {int /*<<< orphan*/  lock; scalar_t__ pinconf_base; } ;
struct TYPE_6__ {int pull_shift; scalar_t__ offset; } ;
struct ns2_pin {TYPE_3__ pin_conf; } ;
struct TYPE_5__ {TYPE_1__* pins; } ;
struct TYPE_4__ {struct ns2_pin* drv_data; } ;

/* Variables and functions */
 int NS2_PIN_PULL_DOWN ; 
 int NS2_PIN_PULL_MASK ; 
 int NS2_PIN_PULL_UP ; 
 struct ns2_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ns2_pin_get_pull(struct pinctrl_dev *pctrldev,
			     unsigned int pin, bool *pull_up,
			     bool *pull_down)
{
	struct ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrldev);
	struct ns2_pin *pin_data = pctrldev->desc->pins[pin].drv_data;
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&pinctrl->lock, flags);
	val = readl(pinctrl->pinconf_base + pin_data->pin_conf.offset);
	val = (val >> pin_data->pin_conf.pull_shift) & NS2_PIN_PULL_MASK;
	*pull_up = false;
	*pull_down = false;

	if (val == NS2_PIN_PULL_UP)
		*pull_up = true;

	if (val == NS2_PIN_PULL_DOWN)
		*pull_down = true;
	spin_unlock_irqrestore(&pinctrl->lock, flags);
}