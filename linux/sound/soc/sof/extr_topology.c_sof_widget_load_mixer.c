#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sof_ipc_comp_reply {int dummy; } ;
struct TYPE_7__ {int size; int cmd; } ;
struct TYPE_8__ {int pipeline_id; TYPE_2__ hdr; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int size; } ;
struct TYPE_9__ {TYPE_1__ hdr; } ;
struct sof_ipc_comp_mixer {TYPE_3__ comp; TYPE_4__ config; } ;
struct snd_sof_widget {struct sof_ipc_comp_mixer* private; int /*<<< orphan*/  comp_id; } ;
struct snd_sof_dev {int /*<<< orphan*/  ipc; int /*<<< orphan*/  dev; } ;
struct snd_soc_tplg_private {int /*<<< orphan*/  size; int /*<<< orphan*/  array; } ;
struct snd_soc_tplg_dapm_widget {struct snd_soc_tplg_private priv; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SOF_COMP_MIXER ; 
 int SOF_IPC_GLB_TPLG_MSG ; 
 int SOF_IPC_TPLG_COMP_NEW ; 
 int /*<<< orphan*/  comp_tokens ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sof_ipc_comp_mixer*) ; 
 struct sof_ipc_comp_mixer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  sof_dbg_comp_config (struct snd_soc_component*,TYPE_4__*) ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int,struct sof_ipc_comp_mixer*,int,struct sof_ipc_comp_reply*,int) ; 
 int sof_parse_tokens (struct snd_soc_component*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sof_widget_load_mixer(struct snd_soc_component *scomp, int index,
				 struct snd_sof_widget *swidget,
				 struct snd_soc_tplg_dapm_widget *tw,
				 struct sof_ipc_comp_reply *r)
{
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	struct snd_soc_tplg_private *private = &tw->priv;
	struct sof_ipc_comp_mixer *mixer;
	int ret;

	mixer = kzalloc(sizeof(*mixer), GFP_KERNEL);
	if (!mixer)
		return -ENOMEM;

	/* configure mixer IPC message */
	mixer->comp.hdr.size = sizeof(*mixer);
	mixer->comp.hdr.cmd = SOF_IPC_GLB_TPLG_MSG | SOF_IPC_TPLG_COMP_NEW;
	mixer->comp.id = swidget->comp_id;
	mixer->comp.type = SOF_COMP_MIXER;
	mixer->comp.pipeline_id = index;
	mixer->config.hdr.size = sizeof(mixer->config);

	ret = sof_parse_tokens(scomp, &mixer->config, comp_tokens,
			       ARRAY_SIZE(comp_tokens), private->array,
			       le32_to_cpu(private->size));
	if (ret != 0) {
		dev_err(sdev->dev, "error: parse mixer.cfg tokens failed %d\n",
			private->size);
		kfree(mixer);
		return ret;
	}

	sof_dbg_comp_config(scomp, &mixer->config);

	swidget->private = mixer;

	ret = sof_ipc_tx_message(sdev->ipc, mixer->comp.hdr.cmd, mixer,
				 sizeof(*mixer), r, sizeof(*r));
	if (ret < 0)
		kfree(mixer);

	return ret;
}