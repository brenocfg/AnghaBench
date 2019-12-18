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
struct TYPE_2__ {int /*<<< orphan*/  bit_width; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channel_allocation; int /*<<< orphan*/  datatype; int /*<<< orphan*/  hdmi_cfg_minor_version; } ;
union afe_port_config {TYPE_1__ hdmi_multi_ch; } ;
struct q6afe_port {union afe_port_config port_cfg; } ;
struct q6afe_hdmi_cfg {int /*<<< orphan*/  bit_width; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channel_allocation; int /*<<< orphan*/  datatype; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_API_VERSION_HDMI_CONFIG ; 

void q6afe_hdmi_port_prepare(struct q6afe_port *port,
			     struct q6afe_hdmi_cfg *cfg)
{
	union afe_port_config *pcfg = &port->port_cfg;

	pcfg->hdmi_multi_ch.hdmi_cfg_minor_version =
					AFE_API_VERSION_HDMI_CONFIG;
	pcfg->hdmi_multi_ch.datatype = cfg->datatype;
	pcfg->hdmi_multi_ch.channel_allocation = cfg->channel_allocation;
	pcfg->hdmi_multi_ch.sample_rate = cfg->sample_rate;
	pcfg->hdmi_multi_ch.bit_width = cfg->bit_width;
}