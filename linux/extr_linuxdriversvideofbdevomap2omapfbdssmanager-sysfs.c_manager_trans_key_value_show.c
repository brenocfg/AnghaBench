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
struct omap_overlay_manager_info {int trans_key; } ;
struct omap_overlay_manager {int /*<<< orphan*/  (* get_manager_info ) (struct omap_overlay_manager*,struct omap_overlay_manager_info*) ;} ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct omap_overlay_manager*,struct omap_overlay_manager_info*) ; 

__attribute__((used)) static ssize_t manager_trans_key_value_show(struct omap_overlay_manager *mgr,
					    char *buf)
{
	struct omap_overlay_manager_info info;

	mgr->get_manager_info(mgr, &info);

	return snprintf(buf, PAGE_SIZE, "%#x\n", info.trans_key);
}