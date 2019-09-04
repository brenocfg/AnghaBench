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
struct mtk_pinctrl {int /*<<< orphan*/  pctl_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;
struct TYPE_4__ {int /*<<< orphan*/  eintmux; } ;
struct mtk_desc_pin {TYPE_1__ pin; TYPE_2__ eint; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PIN_CONFIG_INPUT_ENABLE ; 
 struct mtk_desc_pin* mtk_find_pin_by_eint_num (struct mtk_pinctrl*,unsigned long) ; 
 int /*<<< orphan*/  mtk_pconf_set_ies_smt (struct mtk_pinctrl*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_pmx_gpio_set_direction (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_pmx_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_xt_set_gpio_as_eint(void *data, unsigned long eint_n)
{
	struct mtk_pinctrl *pctl = (struct mtk_pinctrl *)data;
	const struct mtk_desc_pin *pin;

	pin = mtk_find_pin_by_eint_num(pctl, eint_n);
	if (!pin)
		return -EINVAL;

	/* set mux to INT mode */
	mtk_pmx_set_mode(pctl->pctl_dev, pin->pin.number, pin->eint.eintmux);
	/* set gpio direction to input */
	mtk_pmx_gpio_set_direction(pctl->pctl_dev, NULL, pin->pin.number,
				   true);
	/* set input-enable */
	mtk_pconf_set_ies_smt(pctl, pin->pin.number, 1,
			      PIN_CONFIG_INPUT_ENABLE);

	return 0;
}