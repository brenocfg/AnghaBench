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
struct omap_overlay_manager_info {int dummy; } ;
struct omap_overlay_manager {int dummy; } ;
struct mgr_priv_data {struct omap_overlay_manager_info user_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  data_lock ; 
 struct mgr_priv_data* get_mgr_priv (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dss_mgr_get_info(struct omap_overlay_manager *mgr,
		struct omap_overlay_manager_info *info)
{
	struct mgr_priv_data *mp = get_mgr_priv(mgr);
	unsigned long flags;

	spin_lock_irqsave(&data_lock, flags);

	*info = mp->user_info;

	spin_unlock_irqrestore(&data_lock, flags);
}