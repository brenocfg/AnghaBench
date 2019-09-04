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
struct omap_overlay_manager {int dummy; } ;
struct omap_dss_device {int dummy; } ;
struct TYPE_3__ {struct omap_overlay_manager* manager; } ;
struct TYPE_4__ {int /*<<< orphan*/  vdda_dac_reg; TYPE_1__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  VENC_OUTPUT_CONTROL ; 
 int /*<<< orphan*/  dss_mgr_disable (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  dss_set_dac_pwrdn_bgz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 TYPE_2__ venc ; 
 int /*<<< orphan*/  venc_runtime_put () ; 
 int /*<<< orphan*/  venc_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void venc_power_off(struct omap_dss_device *dssdev)
{
	struct omap_overlay_manager *mgr = venc.output.manager;

	venc_write_reg(VENC_OUTPUT_CONTROL, 0);
	dss_set_dac_pwrdn_bgz(0);

	dss_mgr_disable(mgr);

	regulator_disable(venc.vdda_dac_reg);

	venc_runtime_put();
}