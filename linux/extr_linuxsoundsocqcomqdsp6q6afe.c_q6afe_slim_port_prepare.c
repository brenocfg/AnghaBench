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
struct TYPE_2__ {int /*<<< orphan*/ * shared_ch_mapping; int /*<<< orphan*/  data_format; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  bit_width; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  sb_cfg_minor_version; } ;
union afe_port_config {TYPE_1__ slim_cfg; } ;
struct q6afe_slim_cfg {int /*<<< orphan*/ * ch_mapping; int /*<<< orphan*/  data_format; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  bit_width; int /*<<< orphan*/  sample_rate; } ;
struct q6afe_port {union afe_port_config port_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_API_VERSION_SLIMBUS_CONFIG ; 

void q6afe_slim_port_prepare(struct q6afe_port *port,
			     struct q6afe_slim_cfg *cfg)
{
	union afe_port_config *pcfg = &port->port_cfg;

	pcfg->slim_cfg.sb_cfg_minor_version = AFE_API_VERSION_SLIMBUS_CONFIG;
	pcfg->slim_cfg.sample_rate = cfg->sample_rate;
	pcfg->slim_cfg.bit_width = cfg->bit_width;
	pcfg->slim_cfg.num_channels = cfg->num_channels;
	pcfg->slim_cfg.data_format = cfg->data_format;
	pcfg->slim_cfg.shared_ch_mapping[0] = cfg->ch_mapping[0];
	pcfg->slim_cfg.shared_ch_mapping[1] = cfg->ch_mapping[1];
	pcfg->slim_cfg.shared_ch_mapping[2] = cfg->ch_mapping[2];
	pcfg->slim_cfg.shared_ch_mapping[3] = cfg->ch_mapping[3];

}