#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wm8350 {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  nowayout ; 
 struct wm8350* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct wm8350*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ wm8350_wdt ; 
 int /*<<< orphan*/  wm8350_wdt_set_timeout (TYPE_1__*,int) ; 

__attribute__((used)) static int wm8350_wdt_probe(struct platform_device *pdev)
{
	struct wm8350 *wm8350 = platform_get_drvdata(pdev);

	if (!wm8350) {
		pr_err("No driver data supplied\n");
		return -ENODEV;
	}

	watchdog_set_nowayout(&wm8350_wdt, nowayout);
	watchdog_set_drvdata(&wm8350_wdt, wm8350);
	wm8350_wdt.parent = &pdev->dev;

	/* Default to 4s timeout */
	wm8350_wdt_set_timeout(&wm8350_wdt, 4);

	return watchdog_register_device(&wm8350_wdt);
}