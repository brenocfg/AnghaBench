#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sof_widget_data {int /*<<< orphan*/  ctrl_type; int /*<<< orphan*/  ipc_cmd; TYPE_8__* control; TYPE_7__* pdata; } ;
struct TYPE_9__ {TYPE_8__* private; } ;
struct soc_mixer_control {TYPE_1__ dobj; } ;
struct TYPE_11__ {TYPE_8__* private; } ;
struct soc_enum {TYPE_3__ dobj; } ;
struct TYPE_10__ {TYPE_8__* private; } ;
struct soc_bytes_ext {TYPE_2__ dobj; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {int kcontrol_type; } ;
struct TYPE_13__ {TYPE_4__ widget; } ;
struct snd_soc_dapm_widget {int num_kcontrols; int /*<<< orphan*/  name; TYPE_5__ dobj; struct snd_kcontrol_new* kcontrol_news; } ;
struct snd_kcontrol_new {scalar_t__ private_value; } ;
struct TYPE_16__ {int cmd; TYPE_6__* control_data; } ;
struct TYPE_15__ {scalar_t__ magic; scalar_t__ size; } ;
struct TYPE_14__ {TYPE_7__* data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_TPLG_TYPE_BYTES 134 
#define  SND_SOC_TPLG_TYPE_ENUM 133 
#define  SND_SOC_TPLG_TYPE_MIXER 132 
 scalar_t__ SOF_ABI_MAGIC ; 
#define  SOF_CTRL_CMD_BINARY 131 
#define  SOF_CTRL_CMD_ENUM 130 
#define  SOF_CTRL_CMD_SWITCH 129 
#define  SOF_CTRL_CMD_VOLUME 128 
 int /*<<< orphan*/  SOF_CTRL_TYPE_DATA_SET ; 
 int /*<<< orphan*/  SOF_CTRL_TYPE_VALUE_CHAN_SET ; 
 int /*<<< orphan*/  SOF_IPC_COMP_SET_DATA ; 
 int /*<<< orphan*/  SOF_IPC_COMP_SET_VALUE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int sof_get_control_data(struct snd_sof_dev *sdev,
				struct snd_soc_dapm_widget *widget,
				struct sof_widget_data *wdata,
				size_t *size)
{
	const struct snd_kcontrol_new *kc;
	struct soc_mixer_control *sm;
	struct soc_bytes_ext *sbe;
	struct soc_enum *se;
	int i;

	*size = 0;

	for (i = 0; i < widget->num_kcontrols; i++) {
		kc = &widget->kcontrol_news[i];

		switch (widget->dobj.widget.kcontrol_type) {
		case SND_SOC_TPLG_TYPE_MIXER:
			sm = (struct soc_mixer_control *)kc->private_value;
			wdata[i].control = sm->dobj.private;
			break;
		case SND_SOC_TPLG_TYPE_BYTES:
			sbe = (struct soc_bytes_ext *)kc->private_value;
			wdata[i].control = sbe->dobj.private;
			break;
		case SND_SOC_TPLG_TYPE_ENUM:
			se = (struct soc_enum *)kc->private_value;
			wdata[i].control = se->dobj.private;
			break;
		default:
			dev_err(sdev->dev, "error: unknown kcontrol type %d in widget %s\n",
				widget->dobj.widget.kcontrol_type,
				widget->name);
			return -EINVAL;
		}

		if (!wdata[i].control) {
			dev_err(sdev->dev, "error: no scontrol for widget %s\n",
				widget->name);
			return -EINVAL;
		}

		wdata[i].pdata = wdata[i].control->control_data->data;
		if (!wdata[i].pdata)
			return -EINVAL;

		/* make sure data is valid - data can be updated at runtime */
		if (wdata[i].pdata->magic != SOF_ABI_MAGIC)
			return -EINVAL;

		*size += wdata[i].pdata->size;

		/* get data type */
		switch (wdata[i].control->cmd) {
		case SOF_CTRL_CMD_VOLUME:
		case SOF_CTRL_CMD_ENUM:
		case SOF_CTRL_CMD_SWITCH:
			wdata[i].ipc_cmd = SOF_IPC_COMP_SET_VALUE;
			wdata[i].ctrl_type = SOF_CTRL_TYPE_VALUE_CHAN_SET;
			break;
		case SOF_CTRL_CMD_BINARY:
			wdata[i].ipc_cmd = SOF_IPC_COMP_SET_DATA;
			wdata[i].ctrl_type = SOF_CTRL_TYPE_DATA_SET;
			break;
		default:
			break;
		}
	}

	return 0;
}