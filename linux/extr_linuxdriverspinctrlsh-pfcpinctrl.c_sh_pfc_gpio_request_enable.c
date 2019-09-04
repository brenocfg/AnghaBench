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
struct sh_pfc_pinctrl {struct sh_pfc_pin_config* configs; struct sh_pfc* pfc; } ;
struct sh_pfc_pin_config {scalar_t__ type; } ;
struct sh_pfc_pin {int /*<<< orphan*/  enum_id; } ;
struct sh_pfc {int /*<<< orphan*/  lock; TYPE_1__* info; int /*<<< orphan*/  gpio; int /*<<< orphan*/  dev; } ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {struct sh_pfc_pin* pins; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ PINMUX_TYPE_GPIO ; 
 scalar_t__ PINMUX_TYPE_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct sh_pfc_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int sh_pfc_config_mux (struct sh_pfc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int sh_pfc_get_pin_index (struct sh_pfc*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sh_pfc_gpio_request_enable(struct pinctrl_dev *pctldev,
				      struct pinctrl_gpio_range *range,
				      unsigned offset)
{
	struct sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);
	struct sh_pfc *pfc = pmx->pfc;
	int idx = sh_pfc_get_pin_index(pfc, offset);
	struct sh_pfc_pin_config *cfg = &pmx->configs[idx];
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&pfc->lock, flags);

	if (cfg->type != PINMUX_TYPE_NONE) {
		dev_err(pfc->dev,
			"Pin %u is busy, can't configure it as GPIO.\n",
			offset);
		ret = -EBUSY;
		goto done;
	}

	if (!pfc->gpio) {
		/* If GPIOs are handled externally the pin mux type need to be
		 * set to GPIO here.
		 */
		const struct sh_pfc_pin *pin = &pfc->info->pins[idx];

		ret = sh_pfc_config_mux(pfc, pin->enum_id, PINMUX_TYPE_GPIO);
		if (ret < 0)
			goto done;
	}

	cfg->type = PINMUX_TYPE_GPIO;

	ret = 0;

done:
	spin_unlock_irqrestore(&pfc->lock, flags);

	return ret;
}