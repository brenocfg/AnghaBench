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
struct snd_sof_widget {TYPE_2__* widget; struct snd_sof_dev* sdev; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct snd_sof_widget* private; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  name; TYPE_1__ dobj; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  SOF_IPC_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SOF_IPC_STREAM_PCM_FREE ; 
 int /*<<< orphan*/  SOF_IPC_STREAM_TRIG_START ; 
 int /*<<< orphan*/  SOF_IPC_STREAM_TRIG_STOP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ipc_pcm_params (struct snd_sof_widget*,int /*<<< orphan*/ ) ; 
 int ipc_trigger (struct snd_sof_widget*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sof_keyword_dapm_event(struct snd_soc_dapm_widget *w,
				  struct snd_kcontrol *k, int event)
{
	struct snd_sof_widget *swidget = w->dobj.private;
	struct snd_sof_dev *sdev;
	int ret = 0;

	if (!swidget)
		return 0;

	sdev = swidget->sdev;

	dev_dbg(sdev->dev, "received event %d for widget %s\n",
		event, w->name);

	/* process events */
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* set pcm params */
		ret = ipc_pcm_params(swidget, SOF_IPC_STREAM_CAPTURE);
		if (ret < 0) {
			dev_err(sdev->dev,
				"error: failed to set pcm params for widget %s\n",
				swidget->widget->name);
			break;
		}

		/* start trigger */
		ret = ipc_trigger(swidget, SOF_IPC_STREAM_TRIG_START);
		if (ret < 0)
			dev_err(sdev->dev,
				"error: failed to trigger widget %s\n",
				swidget->widget->name);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* stop trigger */
		ret = ipc_trigger(swidget, SOF_IPC_STREAM_TRIG_STOP);
		if (ret < 0)
			dev_err(sdev->dev,
				"error: failed to trigger widget %s\n",
				swidget->widget->name);

		/* pcm free */
		ret = ipc_trigger(swidget, SOF_IPC_STREAM_PCM_FREE);
		if (ret < 0)
			dev_err(sdev->dev,
				"error: failed to trigger widget %s\n",
				swidget->widget->name);
		break;
	default:
		break;
	}

	return ret;
}