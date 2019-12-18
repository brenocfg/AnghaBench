#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sof_ipc_comp_reply {int dummy; } ;
struct TYPE_4__ {int size; int cmd; } ;
struct TYPE_5__ {int pipeline_id; TYPE_1__ hdr; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct sof_ipc_buffer {TYPE_2__ comp; int /*<<< orphan*/  caps; int /*<<< orphan*/  size; } ;
struct snd_sof_widget {TYPE_3__* widget; struct sof_ipc_buffer* private; int /*<<< orphan*/  comp_id; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;
struct snd_soc_tplg_private {int /*<<< orphan*/  size; int /*<<< orphan*/  array; } ;
struct snd_soc_tplg_dapm_widget {struct snd_soc_tplg_private priv; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SOF_COMP_BUFFER ; 
 int SOF_IPC_GLB_TPLG_MSG ; 
 int SOF_IPC_TPLG_BUFFER_NEW ; 
 int /*<<< orphan*/  buffer_tokens ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sof_ipc_buffer*) ; 
 struct sof_ipc_buffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int,struct sof_ipc_buffer*,int,struct sof_ipc_comp_reply*,int) ; 
 int sof_parse_tokens (struct snd_soc_component*,struct sof_ipc_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sof_widget_load_buffer(struct snd_soc_component *scomp, int index,
				  struct snd_sof_widget *swidget,
				  struct snd_soc_tplg_dapm_widget *tw,
				  struct sof_ipc_comp_reply *r)
{
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	struct snd_soc_tplg_private *private = &tw->priv;
	struct sof_ipc_buffer *buffer;
	int ret;

	buffer = kzalloc(sizeof(*buffer), GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	/* configure dai IPC message */
	buffer->comp.hdr.size = sizeof(*buffer);
	buffer->comp.hdr.cmd = SOF_IPC_GLB_TPLG_MSG | SOF_IPC_TPLG_BUFFER_NEW;
	buffer->comp.id = swidget->comp_id;
	buffer->comp.type = SOF_COMP_BUFFER;
	buffer->comp.pipeline_id = index;

	ret = sof_parse_tokens(scomp, buffer, buffer_tokens,
			       ARRAY_SIZE(buffer_tokens), private->array,
			       le32_to_cpu(private->size));
	if (ret != 0) {
		dev_err(sdev->dev, "error: parse buffer tokens failed %d\n",
			private->size);
		kfree(buffer);
		return ret;
	}

	dev_dbg(sdev->dev, "buffer %s: size %d caps 0x%x\n",
		swidget->widget->name, buffer->size, buffer->caps);

	swidget->private = buffer;

	ret = sof_ipc_tx_message(sdev->ipc, buffer->comp.hdr.cmd, buffer,
				 sizeof(*buffer), r, sizeof(*r));
	if (ret < 0) {
		dev_err(sdev->dev, "error: buffer %s load failed\n",
			swidget->widget->name);
		kfree(buffer);
	}

	return ret;
}