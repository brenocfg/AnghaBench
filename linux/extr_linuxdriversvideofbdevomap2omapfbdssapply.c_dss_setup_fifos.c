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
struct omap_overlay_manager {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dss_mgr_setup_fifos (struct omap_overlay_manager*) ; 
 int omap_dss_get_num_overlay_managers () ; 
 struct omap_overlay_manager* omap_dss_get_overlay_manager (int) ; 

__attribute__((used)) static void dss_setup_fifos(void)
{
	const int num_mgrs = omap_dss_get_num_overlay_managers();
	struct omap_overlay_manager *mgr;
	int i;

	for (i = 0; i < num_mgrs; ++i) {
		mgr = omap_dss_get_overlay_manager(i);
		dss_mgr_setup_fifos(mgr);
	}
}