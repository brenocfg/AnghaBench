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
struct omap_overlay_manager_info {int trans_enabled; } ;
struct omap_overlay_manager {int (* set_manager_info ) (struct omap_overlay_manager*,struct omap_overlay_manager_info*) ;int (* apply ) (struct omap_overlay_manager*) ;int /*<<< orphan*/  (* get_manager_info ) (struct omap_overlay_manager*,struct omap_overlay_manager_info*) ;} ;
typedef  int ssize_t ;

/* Variables and functions */
 int strtobool (char const*,int*) ; 
 int /*<<< orphan*/  stub1 (struct omap_overlay_manager*,struct omap_overlay_manager_info*) ; 
 int stub2 (struct omap_overlay_manager*,struct omap_overlay_manager_info*) ; 
 int stub3 (struct omap_overlay_manager*) ; 

__attribute__((used)) static ssize_t manager_trans_key_enabled_store(struct omap_overlay_manager *mgr,
					       const char *buf, size_t size)
{
	struct omap_overlay_manager_info info;
	bool enable;
	int r;

	r = strtobool(buf, &enable);
	if (r)
		return r;

	mgr->get_manager_info(mgr, &info);

	info.trans_enabled = enable;

	r = mgr->set_manager_info(mgr, &info);
	if (r)
		return r;

	r = mgr->apply(mgr);
	if (r)
		return r;

	return size;
}