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
struct TYPE_3__ {int /*<<< orphan*/  slot_mask; int /*<<< orphan*/  slot_width; int /*<<< orphan*/  nslots_per_frame; int /*<<< orphan*/  sync_src; int /*<<< orphan*/  sync_mode; int /*<<< orphan*/  data_format; int /*<<< orphan*/  bit_width; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  tdm_cfg_minor_version; } ;
union afe_port_config {TYPE_1__ tdm_cfg; } ;
typedef  int /*<<< orphan*/  u16 ;
struct q6afe_tdm_cfg {int /*<<< orphan*/  ch_mapping; int /*<<< orphan*/  data_align_type; int /*<<< orphan*/  bit_width; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  slot_mask; int /*<<< orphan*/  slot_width; int /*<<< orphan*/  nslots_per_frame; int /*<<< orphan*/  sync_src; int /*<<< orphan*/  sync_mode; int /*<<< orphan*/  data_format; int /*<<< orphan*/  sample_rate; } ;
struct q6afe_port {TYPE_2__* scfg; union afe_port_config port_cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  ch_mapping; int /*<<< orphan*/  data_align_type; int /*<<< orphan*/  bitwidth; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  minor_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_API_VERSION_SLOT_MAPPING_CONFIG ; 
 int /*<<< orphan*/  AFE_API_VERSION_TDM_CONFIG ; 
 int AFE_PORT_MAX_AUDIO_CHAN_CNT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void q6afe_tdm_port_prepare(struct q6afe_port *port,
			     struct q6afe_tdm_cfg *cfg)
{
	union afe_port_config *pcfg = &port->port_cfg;

	pcfg->tdm_cfg.tdm_cfg_minor_version = AFE_API_VERSION_TDM_CONFIG;
	pcfg->tdm_cfg.num_channels = cfg->num_channels;
	pcfg->tdm_cfg.sample_rate = cfg->sample_rate;
	pcfg->tdm_cfg.bit_width = cfg->bit_width;
	pcfg->tdm_cfg.data_format = cfg->data_format;
	pcfg->tdm_cfg.sync_mode = cfg->sync_mode;
	pcfg->tdm_cfg.sync_src = cfg->sync_src;
	pcfg->tdm_cfg.nslots_per_frame = cfg->nslots_per_frame;

	pcfg->tdm_cfg.slot_width = cfg->slot_width;
	pcfg->tdm_cfg.slot_mask = cfg->slot_mask;
	port->scfg = kzalloc(sizeof(*port->scfg), GFP_KERNEL);
	if (!port->scfg)
		return;

	port->scfg->minor_version = AFE_API_VERSION_SLOT_MAPPING_CONFIG;
	port->scfg->num_channels = cfg->num_channels;
	port->scfg->bitwidth = cfg->bit_width;
	port->scfg->data_align_type = cfg->data_align_type;
	memcpy(port->scfg->ch_mapping, cfg->ch_mapping,
			sizeof(u16) * AFE_PORT_MAX_AUDIO_CHAN_CNT);
}