#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int /*<<< orphan*/  dev; TYPE_2__* desc; } ;
struct cygnus_pinctrl {int /*<<< orphan*/  lock; scalar_t__ base1; } ;
struct cygnus_gpio_mux {int shift; scalar_t__ offset; int /*<<< orphan*/  is_supported; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct TYPE_3__ {struct cygnus_gpio_mux* drv_data; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,scalar_t__,int) ; 
 struct cygnus_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int cygnus_gpio_request_enable(struct pinctrl_dev *pctrl_dev,
				      struct pinctrl_gpio_range *range,
				      unsigned pin)
{
	struct cygnus_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);
	const struct cygnus_gpio_mux *mux = pctrl_dev->desc->pins[pin].drv_data;
	u32 val;
	unsigned long flags;

	/* not all pins support GPIO pinmux override */
	if (!mux->is_supported)
		return -ENOTSUPP;

	spin_lock_irqsave(&pinctrl->lock, flags);

	val = readl(pinctrl->base1 + mux->offset);
	val |= 0x3 << mux->shift;
	writel(val, pinctrl->base1 + mux->offset);

	spin_unlock_irqrestore(&pinctrl->lock, flags);

	dev_dbg(pctrl_dev->dev,
		"gpio request enable pin=%u offset=0x%x shift=%u\n",
		pin, mux->offset, mux->shift);

	return 0;
}