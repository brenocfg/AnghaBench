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
typedef  int u32 ;
struct sof_ipc_reply {int dummy; } ;
struct TYPE_2__ {int size; int /*<<< orphan*/  cmd; } ;
struct sof_ipc_dai_config {int /*<<< orphan*/  dai_index; TYPE_1__ hdr; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;
struct snd_soc_tplg_link_config {int dummy; } ;
struct snd_soc_tplg_hw_config {int dummy; } ;
struct snd_soc_dai_link {int dummy; } ;
struct snd_soc_component {int dummy; } ;
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sof_ipc_dai_config*,int,struct sof_ipc_reply*,int) ; 
 int sof_set_dai_config (struct snd_sof_dev*,int,struct snd_soc_dai_link*,struct sof_ipc_dai_config*) ; 

__attribute__((used)) static int sof_link_alh_load(struct snd_soc_component *scomp, int index,
			     struct snd_soc_dai_link *link,
			     struct snd_soc_tplg_link_config *cfg,
			     struct snd_soc_tplg_hw_config *hw_config,
			     struct sof_ipc_dai_config *config)
{
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	struct sof_ipc_reply reply;
	u32 size = sizeof(*config);
	int ret;

	/* init IPC */
	config->hdr.size = size;

	/* send message to DSP */
	ret = sof_ipc_tx_message(sdev->ipc,
				 config->hdr.cmd, config, size, &reply,
				 sizeof(reply));

	if (ret < 0) {
		dev_err(sdev->dev, "error: failed to set DAI config for ALH %d\n",
			config->dai_index);
		return ret;
	}

	/* set config for all DAI's with name matching the link name */
	ret = sof_set_dai_config(sdev, size, link, config);
	if (ret < 0)
		dev_err(sdev->dev, "error: failed to save DAI config for ALH %d\n",
			config->dai_index);

	return ret;
}