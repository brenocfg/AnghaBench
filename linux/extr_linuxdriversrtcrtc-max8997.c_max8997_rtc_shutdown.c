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
struct max8997_rtc_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  max8997_rtc_enable_smpl (struct max8997_rtc_info*,int) ; 
 int /*<<< orphan*/  max8997_rtc_enable_wtsr (struct max8997_rtc_info*,int) ; 
 struct max8997_rtc_info* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void max8997_rtc_shutdown(struct platform_device *pdev)
{
	struct max8997_rtc_info *info = platform_get_drvdata(pdev);

	max8997_rtc_enable_wtsr(info, false);
	max8997_rtc_enable_smpl(info, false);
}