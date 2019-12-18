#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sof_ipc_pipe_new {int id; int core; int /*<<< orphan*/  list; struct sof_ipc_pipe_new* private; struct sof_ipc_pipe_new* control_data; struct sof_ipc_pipe_new* volume_table; struct sof_ipc_pipe_new* dai_config; struct snd_soc_dapm_widget* widget; } ;
struct TYPE_6__ {struct sof_ipc_pipe_new* private; } ;
struct soc_mixer_control {int max; TYPE_2__ dobj; } ;
struct TYPE_7__ {struct sof_ipc_pipe_new* private; } ;
struct soc_enum {TYPE_3__ dobj; } ;
struct TYPE_8__ {struct sof_ipc_pipe_new* private; } ;
struct soc_bytes_ext {TYPE_4__ dobj; } ;
struct snd_sof_widget {int id; int core; int /*<<< orphan*/  list; struct snd_sof_widget* private; struct snd_sof_widget* control_data; struct snd_sof_widget* volume_table; struct snd_sof_widget* dai_config; struct snd_soc_dapm_widget* widget; } ;
struct snd_sof_dev {int enabled_cores_mask; int /*<<< orphan*/  dev; } ;
struct snd_sof_dai {int id; int core; int /*<<< orphan*/  list; struct snd_sof_dai* private; struct snd_sof_dai* control_data; struct snd_sof_dai* volume_table; struct snd_sof_dai* dai_config; struct snd_soc_dapm_widget* widget; } ;
struct snd_sof_control {int id; int core; int /*<<< orphan*/  list; struct snd_sof_control* private; struct snd_sof_control* control_data; struct snd_sof_control* volume_table; struct snd_sof_control* dai_config; struct snd_soc_dapm_widget* widget; } ;
struct TYPE_5__ {int kcontrol_type; } ;
struct snd_soc_dobj {TYPE_1__ widget; struct sof_ipc_pipe_new* private; } ;
struct snd_soc_dapm_widget {int num_kcontrols; struct snd_kcontrol_new* kcontrol_news; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol_new {scalar_t__ private_value; } ;

/* Variables and functions */
#define  SND_SOC_TPLG_TYPE_BYTES 133 
#define  SND_SOC_TPLG_TYPE_ENUM 132 
#define  SND_SOC_TPLG_TYPE_MIXER 131 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct sof_ipc_pipe_new*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
#define  snd_soc_dapm_dai_in 130 
#define  snd_soc_dapm_dai_out 129 
#define  snd_soc_dapm_scheduler 128 
 int snd_sof_dsp_core_power_down (struct snd_sof_dev*,int) ; 

__attribute__((used)) static int sof_widget_unload(struct snd_soc_component *scomp,
			     struct snd_soc_dobj *dobj)
{
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	const struct snd_kcontrol_new *kc;
	struct snd_soc_dapm_widget *widget;
	struct sof_ipc_pipe_new *pipeline;
	struct snd_sof_control *scontrol;
	struct snd_sof_widget *swidget;
	struct soc_mixer_control *sm;
	struct soc_bytes_ext *sbe;
	struct snd_sof_dai *dai;
	struct soc_enum *se;
	int ret = 0;
	int i;

	swidget = dobj->private;
	if (!swidget)
		return 0;

	widget = swidget->widget;

	switch (swidget->id) {
	case snd_soc_dapm_dai_in:
	case snd_soc_dapm_dai_out:
		dai = swidget->private;

		if (dai) {
			/* free dai config */
			kfree(dai->dai_config);
			list_del(&dai->list);
		}
		break;
	case snd_soc_dapm_scheduler:

		/* power down the pipeline schedule core */
		pipeline = swidget->private;
		ret = snd_sof_dsp_core_power_down(sdev, 1 << pipeline->core);
		if (ret < 0)
			dev_err(sdev->dev, "error: powering down pipeline schedule core %d\n",
				pipeline->core);

		/* update enabled cores mask */
		sdev->enabled_cores_mask &= ~(1 << pipeline->core);

		break;
	default:
		break;
	}
	for (i = 0; i < widget->num_kcontrols; i++) {
		kc = &widget->kcontrol_news[i];
		switch (dobj->widget.kcontrol_type) {
		case SND_SOC_TPLG_TYPE_MIXER:
			sm = (struct soc_mixer_control *)kc->private_value;
			scontrol = sm->dobj.private;
			if (sm->max > 1)
				kfree(scontrol->volume_table);
			break;
		case SND_SOC_TPLG_TYPE_ENUM:
			se = (struct soc_enum *)kc->private_value;
			scontrol = se->dobj.private;
			break;
		case SND_SOC_TPLG_TYPE_BYTES:
			sbe = (struct soc_bytes_ext *)kc->private_value;
			scontrol = sbe->dobj.private;
			break;
		default:
			dev_warn(sdev->dev, "unsupported kcontrol_type\n");
			goto out;
		}
		kfree(scontrol->control_data);
		list_del(&scontrol->list);
		kfree(scontrol);
	}

out:
	/* free private value */
	kfree(swidget->private);

	/* remove and free swidget object */
	list_del(&swidget->list);
	kfree(swidget);

	return ret;
}