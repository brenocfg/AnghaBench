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
struct TYPE_4__ {int /*<<< orphan*/  ext_mode; int /*<<< orphan*/  update_mode; TYPE_1__* fbdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int OMAPFB_PLANE_GFX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ lcdc ; 

__attribute__((used)) static int omap_lcdc_enable_plane(int plane, int enable)
{
	dev_dbg(lcdc.fbdev->dev,
		"plane %d enable %d update_mode %d ext_mode %d\n",
		plane, enable, lcdc.update_mode, lcdc.ext_mode);
	if (plane != OMAPFB_PLANE_GFX)
		return -EINVAL;

	return 0;
}