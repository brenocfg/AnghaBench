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
struct lcd_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct lcd_panel* fbdev_panel ; 
 int /*<<< orphan*/ * fbdev_pdev ; 
 int /*<<< orphan*/  omapfb_do_probe (int /*<<< orphan*/ *,struct lcd_panel*) ; 

void omapfb_register_panel(struct lcd_panel *panel)
{
	BUG_ON(fbdev_panel != NULL);

	fbdev_panel = panel;
	if (fbdev_pdev != NULL)
		omapfb_do_probe(fbdev_pdev, fbdev_panel);
}