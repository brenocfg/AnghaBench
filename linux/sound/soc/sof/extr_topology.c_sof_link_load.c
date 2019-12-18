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
struct TYPE_4__ {int cmd; } ;
struct sof_ipc_dai_config {int type; scalar_t__ format; TYPE_2__ hdr; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct snd_soc_tplg_private {int /*<<< orphan*/  size; int /*<<< orphan*/  array; } ;
struct snd_soc_tplg_link_config {struct snd_soc_tplg_hw_config* hw_config; int /*<<< orphan*/  default_hw_config_id; int /*<<< orphan*/  num_hw_configs; struct snd_soc_tplg_private priv; } ;
struct snd_soc_tplg_hw_config {int /*<<< orphan*/  fmt; int /*<<< orphan*/  id; } ;
struct snd_soc_dai_link {int nonatomic; int /*<<< orphan*/  no_pcm; TYPE_1__* platforms; } ;
struct snd_soc_component {int dummy; } ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  SOF_DAI_IMX_ESAI 133 
#define  SOF_DAI_IMX_SAI 132 
#define  SOF_DAI_INTEL_ALH 131 
#define  SOF_DAI_INTEL_DMIC 130 
#define  SOF_DAI_INTEL_HDA 129 
#define  SOF_DAI_INTEL_SSP 128 
 int SOF_IPC_DAI_CONFIG ; 
 int SOF_IPC_GLB_DAI_MSG ; 
 int /*<<< orphan*/  dai_link_tokens ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sof_ipc_dai_config*,int /*<<< orphan*/ ,int) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int sof_link_alh_load (struct snd_soc_component*,int,struct snd_soc_dai_link*,struct snd_soc_tplg_link_config*,struct snd_soc_tplg_hw_config*,struct sof_ipc_dai_config*) ; 
 int sof_link_dmic_load (struct snd_soc_component*,int,struct snd_soc_dai_link*,struct snd_soc_tplg_link_config*,struct snd_soc_tplg_hw_config*,struct sof_ipc_dai_config*) ; 
 int sof_link_esai_load (struct snd_soc_component*,int,struct snd_soc_dai_link*,struct snd_soc_tplg_link_config*,struct snd_soc_tplg_hw_config*,struct sof_ipc_dai_config*) ; 
 int sof_link_hda_load (struct snd_soc_component*,int,struct snd_soc_dai_link*,struct snd_soc_tplg_link_config*,struct snd_soc_tplg_hw_config*,struct sof_ipc_dai_config*) ; 
 int sof_link_sai_load (struct snd_soc_component*,int,struct snd_soc_dai_link*,struct snd_soc_tplg_link_config*,struct snd_soc_tplg_hw_config*,struct sof_ipc_dai_config*) ; 
 int sof_link_ssp_load (struct snd_soc_component*,int,struct snd_soc_dai_link*,struct snd_soc_tplg_link_config*,struct snd_soc_tplg_hw_config*,struct sof_ipc_dai_config*) ; 
 int sof_parse_tokens (struct snd_soc_component*,struct sof_ipc_dai_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sof_link_load(struct snd_soc_component *scomp, int index,
			 struct snd_soc_dai_link *link,
			 struct snd_soc_tplg_link_config *cfg)
{
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	struct snd_soc_tplg_private *private = &cfg->priv;
	struct sof_ipc_dai_config config;
	struct snd_soc_tplg_hw_config *hw_config;
	int num_hw_configs;
	int ret;
	int i = 0;

	if (!link->platforms) {
		dev_err(sdev->dev, "error: no platforms\n");
		return -EINVAL;
	}
	link->platforms->name = dev_name(sdev->dev);

	/*
	 * Set nonatomic property for FE dai links as their trigger action
	 * involves IPC's.
	 */
	if (!link->no_pcm) {
		link->nonatomic = true;

		/* nothing more to do for FE dai links */
		return 0;
	}

	/* check we have some tokens - we need at least DAI type */
	if (le32_to_cpu(private->size) == 0) {
		dev_err(sdev->dev, "error: expected tokens for DAI, none found\n");
		return -EINVAL;
	}

	/* Send BE DAI link configurations to DSP */
	memset(&config, 0, sizeof(config));

	/* get any common DAI tokens */
	ret = sof_parse_tokens(scomp, &config, dai_link_tokens,
			       ARRAY_SIZE(dai_link_tokens), private->array,
			       le32_to_cpu(private->size));
	if (ret != 0) {
		dev_err(sdev->dev, "error: parse link tokens failed %d\n",
			le32_to_cpu(private->size));
		return ret;
	}

	/*
	 * DAI links are expected to have at least 1 hw_config.
	 * But some older topologies might have no hw_config for HDA dai links.
	 */
	num_hw_configs = le32_to_cpu(cfg->num_hw_configs);
	if (!num_hw_configs) {
		if (config.type != SOF_DAI_INTEL_HDA) {
			dev_err(sdev->dev, "error: unexpected DAI config count %d!\n",
				le32_to_cpu(cfg->num_hw_configs));
			return -EINVAL;
		}
	} else {
		dev_dbg(sdev->dev, "tplg: %d hw_configs found, default id: %d!\n",
			cfg->num_hw_configs, le32_to_cpu(cfg->default_hw_config_id));

		for (i = 0; i < num_hw_configs; i++) {
			if (cfg->hw_config[i].id == cfg->default_hw_config_id)
				break;
		}

		if (i == num_hw_configs) {
			dev_err(sdev->dev, "error: default hw_config id: %d not found!\n",
				le32_to_cpu(cfg->default_hw_config_id));
			return -EINVAL;
		}
	}

	/* configure dai IPC message */
	hw_config = &cfg->hw_config[i];

	config.hdr.cmd = SOF_IPC_GLB_DAI_MSG | SOF_IPC_DAI_CONFIG;
	config.format = le32_to_cpu(hw_config->fmt);

	/* now load DAI specific data and send IPC - type comes from token */
	switch (config.type) {
	case SOF_DAI_INTEL_SSP:
		ret = sof_link_ssp_load(scomp, index, link, cfg, hw_config,
					&config);
		break;
	case SOF_DAI_INTEL_DMIC:
		ret = sof_link_dmic_load(scomp, index, link, cfg, hw_config,
					 &config);
		break;
	case SOF_DAI_INTEL_HDA:
		ret = sof_link_hda_load(scomp, index, link, cfg, hw_config,
					&config);
		break;
	case SOF_DAI_INTEL_ALH:
		ret = sof_link_alh_load(scomp, index, link, cfg, hw_config,
					&config);
		break;
	case SOF_DAI_IMX_SAI:
		ret = sof_link_sai_load(scomp, index, link, cfg, hw_config,
					&config);
		break;
	case SOF_DAI_IMX_ESAI:
		ret = sof_link_esai_load(scomp, index, link, cfg, hw_config,
					 &config);
		break;
	default:
		dev_err(sdev->dev, "error: invalid DAI type %d\n", config.type);
		ret = -EINVAL;
		break;
	}
	if (ret < 0)
		return ret;

	return 0;
}