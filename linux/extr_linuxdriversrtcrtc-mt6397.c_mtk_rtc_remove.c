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
struct mt6397_rtc {int /*<<< orphan*/  irq; int /*<<< orphan*/  rtc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 struct mt6397_rtc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rtc_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_rtc_remove(struct platform_device *pdev)
{
	struct mt6397_rtc *rtc = platform_get_drvdata(pdev);

	rtc_device_unregister(rtc->rtc_dev);
	free_irq(rtc->irq, rtc->rtc_dev);
	irq_dispose_mapping(rtc->irq);

	return 0;
}