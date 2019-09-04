#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;
struct TYPE_5__ {TYPE_1__ rfbi; } ;
struct omap_dss_device {TYPE_2__ phy; int /*<<< orphan*/ * manager; } ;
struct TYPE_6__ {int /*<<< orphan*/  intf_timings; int /*<<< orphan*/  data_lines; int /*<<< orphan*/  pixel_size; struct omap_dss_device output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int ENODEV ; 
 int dss_mgr_register_framedone_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framedone_callback ; 
 TYPE_3__ rfbi ; 
 int /*<<< orphan*/  rfbi_config_lcd_manager (struct omap_dss_device*) ; 
 int /*<<< orphan*/  rfbi_configure_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rfbi_runtime_get () ; 
 int /*<<< orphan*/  rfbi_runtime_put () ; 
 int /*<<< orphan*/  rfbi_set_timings (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rfbi_display_enable(struct omap_dss_device *dssdev)
{
	struct omap_dss_device *out = &rfbi.output;
	int r;

	if (out->manager == NULL) {
		DSSERR("failed to enable display: no output/manager\n");
		return -ENODEV;
	}

	r = rfbi_runtime_get();
	if (r)
		return r;

	r = dss_mgr_register_framedone_handler(out->manager,
			framedone_callback, NULL);
	if (r) {
		DSSERR("can't get FRAMEDONE irq\n");
		goto err1;
	}

	rfbi_config_lcd_manager(dssdev);

	rfbi_configure_bus(dssdev->phy.rfbi.channel, rfbi.pixel_size,
			rfbi.data_lines);

	rfbi_set_timings(dssdev->phy.rfbi.channel, &rfbi.intf_timings);

	return 0;
err1:
	rfbi_runtime_put();
	return r;
}