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
struct TYPE_2__ {int rr; int rg; int rb; int gr; int gg; int gb; int br; int bg; int bb; } ;
struct omap_overlay_manager_info {TYPE_1__ cpr_coefs; } ;
struct omap_overlay_manager {int /*<<< orphan*/  (* get_manager_info ) (struct omap_overlay_manager*,struct omap_overlay_manager_info*) ;} ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub1 (struct omap_overlay_manager*,struct omap_overlay_manager_info*) ; 

__attribute__((used)) static ssize_t manager_cpr_coef_show(struct omap_overlay_manager *mgr,
		char *buf)
{
	struct omap_overlay_manager_info info;

	mgr->get_manager_info(mgr, &info);

	return snprintf(buf, PAGE_SIZE,
			"%d %d %d %d %d %d %d %d %d\n",
			info.cpr_coefs.rr,
			info.cpr_coefs.rg,
			info.cpr_coefs.rb,
			info.cpr_coefs.gr,
			info.cpr_coefs.gg,
			info.cpr_coefs.gb,
			info.cpr_coefs.br,
			info.cpr_coefs.bg,
			info.cpr_coefs.bb);
}