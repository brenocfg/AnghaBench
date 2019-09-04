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
struct kempld_wdt_data {int /*<<< orphan*/  wdd; } ;

/* Variables and functions */
 int /*<<< orphan*/  kempld_wdt_stop (int /*<<< orphan*/ *) ; 
 struct kempld_wdt_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void kempld_wdt_shutdown(struct platform_device *pdev)
{
	struct kempld_wdt_data *wdt_data = platform_get_drvdata(pdev);

	kempld_wdt_stop(&wdt_data->wdd);
}