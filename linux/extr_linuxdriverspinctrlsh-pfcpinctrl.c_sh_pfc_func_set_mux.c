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
struct sh_pfc_pin_group {unsigned int nr_pins; int /*<<< orphan*/ * mux; int /*<<< orphan*/ * pins; } ;
struct sh_pfc_pin_config {scalar_t__ type; } ;
struct sh_pfc {int /*<<< orphan*/  lock; TYPE_1__* info; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {struct sh_pfc_pin_group* groups; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  PINMUX_TYPE_FUNCTION ; 
 scalar_t__ PINMUX_TYPE_NONE ; 
 struct sh_pfc_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int sh_pfc_config_mux (struct sh_pfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sh_pfc_get_pin_index (struct sh_pfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sh_pfc_func_set_mux(struct pinctrl_dev *pctldev, unsigned selector,
			       unsigned group)
{
	struct sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);
	struct sh_pfc *pfc = pmx->pfc;
	const struct sh_pfc_pin_group *grp = &pfc->info->groups[group];
	unsigned long flags;
	unsigned int i;
	int ret = 0;

	spin_lock_irqsave(&pfc->lock, flags);

	for (i = 0; i < grp->nr_pins; ++i) {
		int idx = sh_pfc_get_pin_index(pfc, grp->pins[i]);
		struct sh_pfc_pin_config *cfg = &pmx->configs[idx];

		if (cfg->type != PINMUX_TYPE_NONE) {
			ret = -EBUSY;
			goto done;
		}
	}

	for (i = 0; i < grp->nr_pins; ++i) {
		ret = sh_pfc_config_mux(pfc, grp->mux[i], PINMUX_TYPE_FUNCTION);
		if (ret < 0)
			break;
	}

done:
	spin_unlock_irqrestore(&pfc->lock, flags);
	return ret;
}