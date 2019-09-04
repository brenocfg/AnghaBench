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
struct TYPE_4__ {int priority; int /*<<< orphan*/  notifier_call; } ;
struct msm_pinctrl {int /*<<< orphan*/  dev; TYPE_2__ restart_nb; TYPE_1__* soc; } ;
struct msm_function {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int nfunctions; struct msm_function* functions; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msm_ps_hold_poweroff ; 
 int /*<<< orphan*/  msm_ps_hold_restart ; 
 int /*<<< orphan*/  pm_power_off ; 
 struct msm_pinctrl* poweroff_pctrl ; 
 scalar_t__ register_restart_handler (TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void msm_pinctrl_setup_pm_reset(struct msm_pinctrl *pctrl)
{
	int i;
	const struct msm_function *func = pctrl->soc->functions;

	for (i = 0; i < pctrl->soc->nfunctions; i++)
		if (!strcmp(func[i].name, "ps_hold")) {
			pctrl->restart_nb.notifier_call = msm_ps_hold_restart;
			pctrl->restart_nb.priority = 128;
			if (register_restart_handler(&pctrl->restart_nb))
				dev_err(pctrl->dev,
					"failed to setup restart handler.\n");
			poweroff_pctrl = pctrl;
			pm_power_off = msm_ps_hold_poweroff;
			break;
		}
}