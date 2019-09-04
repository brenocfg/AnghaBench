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
struct vt8500_rtc {scalar_t__ regbase; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ VT8500_RTC_IS ; 
 struct vt8500_rtc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int vt8500_rtc_remove(struct platform_device *pdev)
{
	struct vt8500_rtc *vt8500_rtc = platform_get_drvdata(pdev);

	/* Disable alarm matching */
	writel(0, vt8500_rtc->regbase + VT8500_RTC_IS);

	return 0;
}