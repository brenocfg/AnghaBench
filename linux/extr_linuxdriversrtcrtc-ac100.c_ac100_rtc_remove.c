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
struct ac100_rtc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ac100_rtc_unregister_clks (struct ac100_rtc_dev*) ; 
 struct ac100_rtc_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ac100_rtc_remove(struct platform_device *pdev)
{
	struct ac100_rtc_dev *chip = platform_get_drvdata(pdev);

	ac100_rtc_unregister_clks(chip);

	return 0;
}