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
struct seq_file {int dummy; } ;
struct pmic_mpp_state {int dummy; } ;
struct pmic_mpp_pad {int out_value; size_t function; char* power_source; char* aout_level; size_t pullup; char* dtest; scalar_t__ paired; scalar_t__ has_pullup; scalar_t__ output_enabled; scalar_t__ input_enabled; int /*<<< orphan*/  is_enabled; } ;
struct pinctrl_dev {TYPE_2__* desc; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct TYPE_3__ {struct pmic_mpp_pad* drv_data; } ;

/* Variables and functions */
 char* PMIC_MPP_PHYSICAL_OFFSET ; 
 int /*<<< orphan*/  PMIC_MPP_REG_RT_STS ; 
 int PMIC_MPP_REG_RT_STS_VAL_MASK ; 
 struct pmic_mpp_state* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 char** pmic_mpp_functions ; 
 int pmic_mpp_read (struct pmic_mpp_state*,struct pmic_mpp_pad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const* const) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void pmic_mpp_config_dbg_show(struct pinctrl_dev *pctldev,
				     struct seq_file *s, unsigned pin)
{
	struct pmic_mpp_state *state = pinctrl_dev_get_drvdata(pctldev);
	struct pmic_mpp_pad *pad;
	int ret;

	static const char *const biases[] = {
		"0.6kOhm", "10kOhm", "30kOhm", "Disabled"
	};

	pad = pctldev->desc->pins[pin].drv_data;

	seq_printf(s, " mpp%-2d:", pin + PMIC_MPP_PHYSICAL_OFFSET);

	if (!pad->is_enabled) {
		seq_puts(s, " ---");
	} else {

		if (pad->input_enabled) {
			ret = pmic_mpp_read(state, pad, PMIC_MPP_REG_RT_STS);
			if (ret < 0)
				return;

			ret &= PMIC_MPP_REG_RT_STS_VAL_MASK;
			pad->out_value = ret;
		}

		seq_printf(s, " %-4s", pad->output_enabled ? "out" : "in");
		seq_printf(s, " %-7s", pmic_mpp_functions[pad->function]);
		seq_printf(s, " vin-%d", pad->power_source);
		seq_printf(s, " %d", pad->aout_level);
		if (pad->has_pullup)
			seq_printf(s, " %-8s", biases[pad->pullup]);
		seq_printf(s, " %-4s", pad->out_value ? "high" : "low");
		if (pad->dtest)
			seq_printf(s, " dtest%d", pad->dtest);
		if (pad->paired)
			seq_puts(s, " paired");
	}
}