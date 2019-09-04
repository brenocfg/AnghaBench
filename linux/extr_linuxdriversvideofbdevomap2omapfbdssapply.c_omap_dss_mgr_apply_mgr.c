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
struct mgr_priv_data {int user_info_dirty; int info_dirty; int /*<<< orphan*/  user_info; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 struct mgr_priv_data* get_mgr_priv (struct omap_overlay_manager*) ; 

__attribute__((used)) static void omap_dss_mgr_apply_mgr(struct omap_overlay_manager *mgr)
{
	struct mgr_priv_data *mp;

	mp = get_mgr_priv(mgr);

	if (!mp->user_info_dirty)
		return;

	mp->user_info_dirty = false;
	mp->info_dirty = true;
	mp->info = mp->user_info;
}