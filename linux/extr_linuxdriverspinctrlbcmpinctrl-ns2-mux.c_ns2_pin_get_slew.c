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
typedef  int u16 ;
struct pinctrl_dev {int /*<<< orphan*/  dev; TYPE_2__* desc; } ;
struct ns2_pinctrl {int /*<<< orphan*/  lock; scalar_t__ pinconf_base; } ;
struct TYPE_4__ {int src_shift; scalar_t__ offset; } ;
struct ns2_pin {TYPE_1__ pin_conf; } ;
struct TYPE_6__ {struct ns2_pin* drv_data; } ;
struct TYPE_5__ {TYPE_3__* pins; } ;

/* Variables and functions */
 int NS2_PIN_SRC_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 struct ns2_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ns2_pin_get_slew(struct pinctrl_dev *pctrldev, unsigned int pin,
			    u16 *slew)
{
	struct ns2_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrldev);
	struct ns2_pin *pin_data = pctrldev->desc->pins[pin].drv_data;
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&pinctrl->lock, flags);
	val = readl(pinctrl->pinconf_base + pin_data->pin_conf.offset);
	*slew = (val >> pin_data->pin_conf.src_shift) & NS2_PIN_SRC_MASK;
	spin_unlock_irqrestore(&pinctrl->lock, flags);

	dev_dbg(pctrldev->dev, "pin:%u get slew:%d\n", pin, *slew);
	return 0;
}