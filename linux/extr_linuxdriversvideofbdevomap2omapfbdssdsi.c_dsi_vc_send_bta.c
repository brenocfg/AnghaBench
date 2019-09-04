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
struct platform_device {int dummy; } ;
struct dsi_data {scalar_t__ debug_read; scalar_t__ debug_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 int /*<<< orphan*/  DSSDBG (char*,int) ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct platform_device*,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ REG_GET (struct platform_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dsi_bus_is_locked (struct platform_device*) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_read_reg (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_vc_flush_receive_data (struct platform_device*,int) ; 

__attribute__((used)) static int dsi_vc_send_bta(struct platform_device *dsidev, int channel)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);

	if (dsi->debug_write || dsi->debug_read)
		DSSDBG("dsi_vc_send_bta %d\n", channel);

	WARN_ON(!dsi_bus_is_locked(dsidev));

	/* RX_FIFO_NOT_EMPTY */
	if (REG_GET(dsidev, DSI_VC_CTRL(channel), 20, 20)) {
		DSSERR("rx fifo not empty when sending BTA, dumping data:\n");
		dsi_vc_flush_receive_data(dsidev, channel);
	}

	REG_FLD_MOD(dsidev, DSI_VC_CTRL(channel), 1, 6, 6); /* BTA_EN */

	/* flush posted write */
	dsi_read_reg(dsidev, DSI_VC_CTRL(channel));

	return 0;
}