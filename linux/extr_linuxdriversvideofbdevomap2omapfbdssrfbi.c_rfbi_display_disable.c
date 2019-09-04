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
struct omap_dss_device {int /*<<< orphan*/  manager; } ;
struct TYPE_2__ {struct omap_dss_device output; } ;

/* Variables and functions */
 int /*<<< orphan*/  dss_mgr_unregister_framedone_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framedone_callback ; 
 TYPE_1__ rfbi ; 
 int /*<<< orphan*/  rfbi_runtime_put () ; 

__attribute__((used)) static void rfbi_display_disable(struct omap_dss_device *dssdev)
{
	struct omap_dss_device *out = &rfbi.output;

	dss_mgr_unregister_framedone_handler(out->manager,
			framedone_callback, NULL);

	rfbi_runtime_put();
}