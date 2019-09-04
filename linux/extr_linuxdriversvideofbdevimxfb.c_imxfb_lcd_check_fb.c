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
struct lcd_device {int /*<<< orphan*/  dev; } ;
struct imxfb_info {int dummy; } ;
struct fb_info {struct imxfb_info* par; } ;

/* Variables and functions */
 struct imxfb_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imxfb_lcd_check_fb(struct lcd_device *lcddev, struct fb_info *fi)
{
	struct imxfb_info *fbi = dev_get_drvdata(&lcddev->dev);

	if (!fi || fi->par == fbi)
		return 1;

	return 0;
}