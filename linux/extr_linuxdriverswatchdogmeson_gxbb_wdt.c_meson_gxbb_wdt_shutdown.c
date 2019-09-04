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
struct meson_gxbb_wdt {int /*<<< orphan*/  wdt_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  meson_gxbb_wdt_stop (int /*<<< orphan*/ *) ; 
 struct meson_gxbb_wdt* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void meson_gxbb_wdt_shutdown(struct platform_device *pdev)
{
	struct meson_gxbb_wdt *data = platform_get_drvdata(pdev);

	meson_gxbb_wdt_stop(&data->wdt_dev);
}