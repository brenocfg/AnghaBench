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
struct TYPE_4__ {int channel_mode; int /*<<< orphan*/  mono_stereo; int /*<<< orphan*/  ws_src; int /*<<< orphan*/  data_format; int /*<<< orphan*/  bit_width; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  i2s_cfg_minor_version; } ;
union afe_port_config {TYPE_2__ i2s_cfg; } ;
struct q6afe_port {TYPE_1__* afe; union afe_port_config port_cfg; } ;
struct q6afe_i2s_cfg {int fmt; int num_channels; int /*<<< orphan*/  sd_line_mask; int /*<<< orphan*/  bit_width; int /*<<< orphan*/  sample_rate; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_API_VERSION_I2S_CONFIG ; 
 int /*<<< orphan*/  AFE_LINEAR_PCM_DATA ; 
 int /*<<< orphan*/  AFE_PORT_CONFIG_I2S_WS_SRC_EXTERNAL ; 
 int /*<<< orphan*/  AFE_PORT_CONFIG_I2S_WS_SRC_INTERNAL ; 
#define  AFE_PORT_I2S_6CHS 141 
#define  AFE_PORT_I2S_8CHS 140 
 int /*<<< orphan*/  AFE_PORT_I2S_MONO ; 
#define  AFE_PORT_I2S_QUAD01 139 
#define  AFE_PORT_I2S_QUAD23 138 
 void* AFE_PORT_I2S_SD0 ; 
#define  AFE_PORT_I2S_SD0_1_2_3_MASK 137 
#define  AFE_PORT_I2S_SD0_1_2_MASK 136 
#define  AFE_PORT_I2S_SD0_1_MASK 135 
#define  AFE_PORT_I2S_SD0_MASK 134 
 int AFE_PORT_I2S_SD1 ; 
#define  AFE_PORT_I2S_SD1_MASK 133 
 void* AFE_PORT_I2S_SD2 ; 
#define  AFE_PORT_I2S_SD2_3_MASK 132 
#define  AFE_PORT_I2S_SD2_MASK 131 
 int AFE_PORT_I2S_SD3 ; 
#define  AFE_PORT_I2S_SD3_MASK 130 
 int /*<<< orphan*/  AFE_PORT_I2S_STEREO ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 129 
#define  SND_SOC_DAIFMT_CBS_CFS 128 
 int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int hweight_long (int /*<<< orphan*/ ) ; 

int q6afe_i2s_port_prepare(struct q6afe_port *port, struct q6afe_i2s_cfg *cfg)
{
	union afe_port_config *pcfg = &port->port_cfg;
	struct device *dev = port->afe->dev;
	int num_sd_lines;

	pcfg->i2s_cfg.i2s_cfg_minor_version = AFE_API_VERSION_I2S_CONFIG;
	pcfg->i2s_cfg.sample_rate = cfg->sample_rate;
	pcfg->i2s_cfg.bit_width = cfg->bit_width;
	pcfg->i2s_cfg.data_format = AFE_LINEAR_PCM_DATA;

	switch (cfg->fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		pcfg->i2s_cfg.ws_src = AFE_PORT_CONFIG_I2S_WS_SRC_INTERNAL;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		/* CPU is slave */
		pcfg->i2s_cfg.ws_src = AFE_PORT_CONFIG_I2S_WS_SRC_EXTERNAL;
		break;
	default:
		break;
	}

	num_sd_lines = hweight_long(cfg->sd_line_mask);

	switch (num_sd_lines) {
	case 0:
		dev_err(dev, "no line is assigned\n");
		return -EINVAL;
	case 1:
		switch (cfg->sd_line_mask) {
		case AFE_PORT_I2S_SD0_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_SD0;
			break;
		case AFE_PORT_I2S_SD1_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_SD1;
			break;
		case AFE_PORT_I2S_SD2_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_SD2;
			break;
		case AFE_PORT_I2S_SD3_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_SD3;
			break;
		default:
			dev_err(dev, "Invalid SD lines\n");
			return -EINVAL;
		}
		break;
	case 2:
		switch (cfg->sd_line_mask) {
		case AFE_PORT_I2S_SD0_1_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_QUAD01;
			break;
		case AFE_PORT_I2S_SD2_3_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_QUAD23;
			break;
		default:
			dev_err(dev, "Invalid SD lines\n");
			return -EINVAL;
		}
		break;
	case 3:
		switch (cfg->sd_line_mask) {
		case AFE_PORT_I2S_SD0_1_2_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_6CHS;
			break;
		default:
			dev_err(dev, "Invalid SD lines\n");
			return -EINVAL;
		}
		break;
	case 4:
		switch (cfg->sd_line_mask) {
		case AFE_PORT_I2S_SD0_1_2_3_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_8CHS;

			break;
		default:
			dev_err(dev, "Invalid SD lines\n");
			return -EINVAL;
		}
		break;
	default:
		dev_err(dev, "Invalid SD lines\n");
		return -EINVAL;
	}

	switch (cfg->num_channels) {
	case 1:
	case 2:
		switch (pcfg->i2s_cfg.channel_mode) {
		case AFE_PORT_I2S_QUAD01:
		case AFE_PORT_I2S_6CHS:
		case AFE_PORT_I2S_8CHS:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_SD0;
			break;
		case AFE_PORT_I2S_QUAD23:
				pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_SD2;
			break;
		}

		if (cfg->num_channels == 2)
			pcfg->i2s_cfg.mono_stereo = AFE_PORT_I2S_STEREO;
		else
			pcfg->i2s_cfg.mono_stereo = AFE_PORT_I2S_MONO;

		break;
	case 3:
	case 4:
		if (pcfg->i2s_cfg.channel_mode < AFE_PORT_I2S_QUAD01) {
			dev_err(dev, "Invalid Channel mode\n");
			return -EINVAL;
		}
		break;
	case 5:
	case 6:
		if (pcfg->i2s_cfg.channel_mode < AFE_PORT_I2S_6CHS) {
			dev_err(dev, "Invalid Channel mode\n");
			return -EINVAL;
		}
		break;
	case 7:
	case 8:
		if (pcfg->i2s_cfg.channel_mode < AFE_PORT_I2S_8CHS) {
			dev_err(dev, "Invalid Channel mode\n");
			return -EINVAL;
		}
		break;
	default:
		break;
	}

	return 0;
}