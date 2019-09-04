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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int flexfb_remove_common (int /*<<< orphan*/ *,struct fb_info*) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int flexfb_remove_pdev(struct platform_device *pdev)
{
	struct fb_info *info = platform_get_drvdata(pdev);

	return flexfb_remove_common(&pdev->dev, info);
}