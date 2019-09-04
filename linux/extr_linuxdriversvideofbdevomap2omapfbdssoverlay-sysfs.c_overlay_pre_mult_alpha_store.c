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
typedef  int /*<<< orphan*/  u8 ;
struct omap_overlay_info {int /*<<< orphan*/  pre_mult_alpha; } ;
struct omap_overlay {int caps; int (* set_overlay_info ) (struct omap_overlay*,struct omap_overlay_info*) ;TYPE_1__* manager; int /*<<< orphan*/  (* get_overlay_info ) (struct omap_overlay*,struct omap_overlay_info*) ;} ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* apply ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA ; 
 int kstrtou8 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct omap_overlay*,struct omap_overlay_info*) ; 
 int stub2 (struct omap_overlay*,struct omap_overlay_info*) ; 
 int stub3 (TYPE_1__*) ; 

__attribute__((used)) static ssize_t overlay_pre_mult_alpha_store(struct omap_overlay *ovl,
		const char *buf, size_t size)
{
	int r;
	u8 alpha;
	struct omap_overlay_info info;

	if ((ovl->caps & OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA) == 0)
		return -ENODEV;

	r = kstrtou8(buf, 0, &alpha);
	if (r)
		return r;

	ovl->get_overlay_info(ovl, &info);

	info.pre_mult_alpha = alpha;

	r = ovl->set_overlay_info(ovl, &info);
	if (r)
		return r;

	if (ovl->manager) {
		r = ovl->manager->apply(ovl->manager);
		if (r)
			return r;
	}

	return size;
}