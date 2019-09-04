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
struct TYPE_4__ {int /*<<< orphan*/  vdds_sdi_reg; TYPE_1__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  dispc_runtime_put () ; 
 int /*<<< orphan*/  dss_mgr_disable (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  dss_sdi_disable () ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 TYPE_2__ sdi ; 

__attribute__((used)) static void sdi_display_disable(struct omap_dss_device *dssdev)
{
	struct omap_overlay_manager *mgr = sdi.output.manager;

	dss_mgr_disable(mgr);

	dss_sdi_disable();

	dispc_runtime_put();

	regulator_disable(sdi.vdds_sdi_reg);
}