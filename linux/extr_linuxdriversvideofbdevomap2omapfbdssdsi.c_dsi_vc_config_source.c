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
struct platform_device {int dummy; } ;
struct dsi_data {TYPE_1__* vc; } ;
typedef  enum dsi_vc_source { ____Placeholder_dsi_vc_source } dsi_vc_source ;
struct TYPE_2__ {int source; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 int DSI_VC_SOURCE_VP ; 
 int /*<<< orphan*/  DSSDBG (char*,int) ; 
 int /*<<< orphan*/  DSSERR (char*,int) ; 
 int EIO ; 
 int /*<<< orphan*/  FEAT_DSI_DCS_CMD_CONFIG_VC ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct platform_device*,int /*<<< orphan*/ ,int,int,int) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_sync_vc (struct platform_device*,int) ; 
 int /*<<< orphan*/  dsi_vc_enable (struct platform_device*,int,int) ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_bit_change (struct platform_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_vc_config_source(struct platform_device *dsidev, int channel,
		enum dsi_vc_source source)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);

	if (dsi->vc[channel].source == source)
		return 0;

	DSSDBG("Source config of virtual channel %d", channel);

	dsi_sync_vc(dsidev, channel);

	dsi_vc_enable(dsidev, channel, 0);

	/* VC_BUSY */
	if (wait_for_bit_change(dsidev, DSI_VC_CTRL(channel), 15, 0) != 0) {
		DSSERR("vc(%d) busy when trying to config for VP\n", channel);
		return -EIO;
	}

	/* SOURCE, 0 = L4, 1 = video port */
	REG_FLD_MOD(dsidev, DSI_VC_CTRL(channel), source, 1, 1);

	/* DCS_CMD_ENABLE */
	if (dss_has_feature(FEAT_DSI_DCS_CMD_CONFIG_VC)) {
		bool enable = source == DSI_VC_SOURCE_VP;
		REG_FLD_MOD(dsidev, DSI_VC_CTRL(channel), enable, 30, 30);
	}

	dsi_vc_enable(dsidev, channel, 1);

	dsi->vc[channel].source = source;

	return 0;
}