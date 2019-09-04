#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct q6afe_port {int dummy; } ;
struct afe_digital_clk_cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_MODULE_AUDIO_DEV_INTERFACE ; 
 int /*<<< orphan*/  AFE_PARAM_ID_INT_DIGITAL_CDC_CLK_CONFIG ; 
 int q6afe_port_set_param_v2 (struct q6afe_port*,struct afe_digital_clk_cfg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int q6afe_set_digital_codec_core_clock(struct q6afe_port *port,
					      struct afe_digital_clk_cfg *cfg)
{
	return q6afe_port_set_param_v2(port, cfg,
				       AFE_PARAM_ID_INT_DIGITAL_CDC_CLK_CONFIG,
				       AFE_MODULE_AUDIO_DEV_INTERFACE,
				       sizeof(*cfg));
}