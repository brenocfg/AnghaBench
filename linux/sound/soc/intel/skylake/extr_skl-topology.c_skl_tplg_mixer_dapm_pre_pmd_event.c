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
struct snd_soc_dapm_widget {struct skl_module_cfg* priv; } ;
struct skl_module_cfg {TYPE_2__* m_in_pin; TYPE_1__* module; int /*<<< orphan*/  pipe; } ;
struct skl_dev {int dummy; } ;
struct TYPE_4__ {scalar_t__ pin_state; struct skl_module_cfg* tgt_mcfg; } ;
struct TYPE_3__ {int max_input_pins; } ;

/* Variables and functions */
 scalar_t__ SKL_PIN_BIND_DONE ; 
 int skl_stop_pipe (struct skl_dev*,int /*<<< orphan*/ ) ; 
 int skl_unbind_modules (struct skl_dev*,struct skl_module_cfg*,struct skl_module_cfg*) ; 

__attribute__((used)) static int skl_tplg_mixer_dapm_pre_pmd_event(struct snd_soc_dapm_widget *w,
							struct skl_dev *skl)
{
	struct skl_module_cfg *src_mconfig, *sink_mconfig;
	int ret = 0, i;

	sink_mconfig = w->priv;

	/* Stop the pipe */
	ret = skl_stop_pipe(skl, sink_mconfig->pipe);
	if (ret)
		return ret;

	for (i = 0; i < sink_mconfig->module->max_input_pins; i++) {
		if (sink_mconfig->m_in_pin[i].pin_state == SKL_PIN_BIND_DONE) {
			src_mconfig = sink_mconfig->m_in_pin[i].tgt_mcfg;
			if (!src_mconfig)
				continue;

			ret = skl_unbind_modules(skl,
						src_mconfig, sink_mconfig);
		}
	}

	return ret;
}