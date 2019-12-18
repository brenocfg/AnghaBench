#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t size; int cmd; } ;
struct TYPE_11__ {int type; int pipeline_id; TYPE_3__ hdr; int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int size; } ;
struct TYPE_12__ {TYPE_1__ hdr; } ;
struct sof_widget_data {size_t size; TYPE_7__* control; int /*<<< orphan*/  ctrl_type; int /*<<< orphan*/  ipc_cmd; TYPE_4__ comp; TYPE_2__* pdata; int /*<<< orphan*/  data; TYPE_5__ config; } ;
struct sof_ipc_comp_reply {int dummy; } ;
struct sof_ipc_comp_process {size_t size; TYPE_7__* control; int /*<<< orphan*/  ctrl_type; int /*<<< orphan*/  ipc_cmd; TYPE_4__ comp; TYPE_2__* pdata; int /*<<< orphan*/  data; TYPE_5__ config; } ;
struct snd_sof_widget {struct sof_widget_data* private; int /*<<< orphan*/  comp_id; struct snd_soc_dapm_widget* widget; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;
struct snd_soc_tplg_private {int /*<<< orphan*/  size; int /*<<< orphan*/  array; } ;
struct snd_soc_tplg_dapm_widget {struct snd_soc_tplg_private priv; } ;
struct snd_soc_dapm_widget {int num_kcontrols; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  cmd; scalar_t__ readback_offset; } ;
struct TYPE_9__ {scalar_t__ size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SOF_COMP_NONE ; 
 int SOF_IPC_GLB_TPLG_MSG ; 
 size_t SOF_IPC_MSG_MAX_SIZE ; 
 int SOF_IPC_TPLG_COMP_NEW ; 
 int /*<<< orphan*/  comp_tokens ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct sof_widget_data* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sof_widget_data*) ; 
 struct sof_widget_data* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_sof_ipc_set_get_comp_data (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sof_dbg_comp_config (struct snd_soc_component*,TYPE_5__*) ; 
 int sof_get_control_data (struct snd_sof_dev*,struct snd_soc_dapm_widget*,struct sof_widget_data*,size_t*) ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int,struct sof_widget_data*,size_t,struct sof_ipc_comp_reply*,int) ; 
 int sof_parse_tokens (struct snd_soc_component*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sof_process_load(struct snd_soc_component *scomp, int index,
			    struct snd_sof_widget *swidget,
			    struct snd_soc_tplg_dapm_widget *tw,
			    struct sof_ipc_comp_reply *r,
			    int type)
{
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	struct snd_soc_dapm_widget *widget = swidget->widget;
	struct snd_soc_tplg_private *private = &tw->priv;
	struct sof_ipc_comp_process *process = NULL;
	struct sof_widget_data *wdata = NULL;
	size_t ipc_data_size = 0;
	size_t ipc_size;
	int offset = 0;
	int ret = 0;
	int i;

	if (type == SOF_COMP_NONE) {
		dev_err(sdev->dev, "error: invalid process comp type %d\n",
			type);
		return -EINVAL;
	}

	/* allocate struct for widget control data sizes and types */
	if (widget->num_kcontrols) {
		wdata = kcalloc(widget->num_kcontrols,
				sizeof(*wdata),
				GFP_KERNEL);

		if (!wdata)
			return -ENOMEM;

		/* get possible component controls and get size of all pdata */
		ret = sof_get_control_data(sdev, widget, wdata,
					   &ipc_data_size);

		if (ret < 0)
			goto out;
	}

	ipc_size = sizeof(struct sof_ipc_comp_process) +
		le32_to_cpu(private->size) +
		ipc_data_size;

	/* we are exceeding max ipc size, config needs to be sent separately */
	if (ipc_size > SOF_IPC_MSG_MAX_SIZE) {
		ipc_size -= ipc_data_size;
		ipc_data_size = 0;
	}

	process = kzalloc(ipc_size, GFP_KERNEL);
	if (!process) {
		ret = -ENOMEM;
		goto out;
	}

	/* configure iir IPC message */
	process->comp.hdr.size = ipc_size;
	process->comp.hdr.cmd = SOF_IPC_GLB_TPLG_MSG | SOF_IPC_TPLG_COMP_NEW;
	process->comp.id = swidget->comp_id;
	process->comp.type = type;
	process->comp.pipeline_id = index;
	process->config.hdr.size = sizeof(process->config);

	ret = sof_parse_tokens(scomp, &process->config, comp_tokens,
			       ARRAY_SIZE(comp_tokens), private->array,
			       le32_to_cpu(private->size));
	if (ret != 0) {
		dev_err(sdev->dev, "error: parse process.cfg tokens failed %d\n",
			le32_to_cpu(private->size));
		goto err;
	}

	sof_dbg_comp_config(scomp, &process->config);

	/*
	 * found private data in control, so copy it.
	 * get possible component controls - get size of all pdata,
	 * then memcpy with headers
	 */
	if (ipc_data_size) {
		for (i = 0; i < widget->num_kcontrols; i++) {
			memcpy(&process->data + offset,
			       wdata[i].pdata->data,
			       wdata[i].pdata->size);
			offset += wdata[i].pdata->size;
		}
	}

	process->size = ipc_data_size;
	swidget->private = process;

	ret = sof_ipc_tx_message(sdev->ipc, process->comp.hdr.cmd, process,
				 ipc_size, r, sizeof(*r));

	if (ret < 0) {
		dev_err(sdev->dev, "error: create process failed\n");
		goto err;
	}

	/* we sent the data in single message so return */
	if (ipc_data_size)
		goto out;

	/* send control data with large message supported method */
	for (i = 0; i < widget->num_kcontrols; i++) {
		wdata[i].control->readback_offset = 0;
		ret = snd_sof_ipc_set_get_comp_data(sdev->ipc, wdata[i].control,
						    wdata[i].ipc_cmd,
						    wdata[i].ctrl_type,
						    wdata[i].control->cmd,
						    true);
		if (ret != 0) {
			dev_err(sdev->dev, "error: send control failed\n");
			break;
		}
	}

err:
	if (ret < 0)
		kfree(process);
out:
	kfree(wdata);
	return ret;
}