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
struct wm8350 {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8350_IRQ_RTC_ALM ; 
 int /*<<< orphan*/  WM8350_IRQ_RTC_SEC ; 
 struct wm8350* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  wm8350_free_irq (struct wm8350*,int /*<<< orphan*/ ,struct wm8350*) ; 

__attribute__((used)) static int wm8350_rtc_remove(struct platform_device *pdev)
{
	struct wm8350 *wm8350 = platform_get_drvdata(pdev);

	wm8350_free_irq(wm8350, WM8350_IRQ_RTC_SEC, wm8350);
	wm8350_free_irq(wm8350, WM8350_IRQ_RTC_ALM, wm8350);

	return 0;
}