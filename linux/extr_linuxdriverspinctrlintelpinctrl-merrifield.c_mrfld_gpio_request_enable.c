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
typedef  int u32 ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct mrfld_pinctrl {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int BUFCFG_PINMODE_GPIO ; 
 int BUFCFG_PINMODE_MASK ; 
 int BUFCFG_PINMODE_SHIFT ; 
 int EBUSY ; 
 int /*<<< orphan*/  mrfld_buf_available (struct mrfld_pinctrl*,unsigned int) ; 
 int /*<<< orphan*/  mrfld_update_bufcfg (struct mrfld_pinctrl*,unsigned int,int,int) ; 
 struct mrfld_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mrfld_gpio_request_enable(struct pinctrl_dev *pctldev,
				     struct pinctrl_gpio_range *range,
				     unsigned int pin)
{
	struct mrfld_pinctrl *mp = pinctrl_dev_get_drvdata(pctldev);
	u32 bits = BUFCFG_PINMODE_GPIO << BUFCFG_PINMODE_SHIFT;
	u32 mask = BUFCFG_PINMODE_MASK;
	unsigned long flags;

	if (!mrfld_buf_available(mp, pin))
		return -EBUSY;

	raw_spin_lock_irqsave(&mp->lock, flags);
	mrfld_update_bufcfg(mp, pin, bits, mask);
	raw_spin_unlock_irqrestore(&mp->lock, flags);

	return 0;
}