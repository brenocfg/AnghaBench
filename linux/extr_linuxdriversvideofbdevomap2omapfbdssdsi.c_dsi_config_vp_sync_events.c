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
typedef  int /*<<< orphan*/  u32 ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ trans_mode; } ;
struct dsi_data {TYPE_1__ vm_timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_CTRL ; 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ OMAP_DSS_DSI_PULSE_MODE ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_read_reg (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write_reg (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_config_vp_sync_events(struct platform_device *dsidev)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	bool sync_end;
	u32 r;

	if (dsi->vm_timings.trans_mode == OMAP_DSS_DSI_PULSE_MODE)
		sync_end = true;
	else
		sync_end = false;

	r = dsi_read_reg(dsidev, DSI_CTRL);
	r = FLD_MOD(r, 1, 9, 9);		/* VP_DE_POL */
	r = FLD_MOD(r, 1, 10, 10);		/* VP_HSYNC_POL */
	r = FLD_MOD(r, 1, 11, 11);		/* VP_VSYNC_POL */
	r = FLD_MOD(r, 1, 15, 15);		/* VP_VSYNC_START */
	r = FLD_MOD(r, sync_end, 16, 16);	/* VP_VSYNC_END */
	r = FLD_MOD(r, 1, 17, 17);		/* VP_HSYNC_START */
	r = FLD_MOD(r, sync_end, 18, 18);	/* VP_HSYNC_END */
	dsi_write_reg(dsidev, DSI_CTRL, r);
}