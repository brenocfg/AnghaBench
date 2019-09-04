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
struct platform_device {int dummy; } ;
struct omapfb2_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  omapdss_compat_uninit () ; 
 int /*<<< orphan*/  omapfb_free_resources (struct omapfb2_device*) ; 
 int /*<<< orphan*/  omapfb_remove_sysfs (struct omapfb2_device*) ; 
 struct omapfb2_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int omapfb_remove(struct platform_device *pdev)
{
	struct omapfb2_device *fbdev = platform_get_drvdata(pdev);

	/* FIXME: wait till completion of pending events */

	omapfb_remove_sysfs(fbdev);

	omapfb_free_resources(fbdev);

	omapdss_compat_uninit();

	return 0;
}