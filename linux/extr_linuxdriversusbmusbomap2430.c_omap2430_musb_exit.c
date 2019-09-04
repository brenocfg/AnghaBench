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
struct omap2430_glue {int /*<<< orphan*/  omap_musb_mailbox_work; } ;
struct musb {int /*<<< orphan*/ * phy; struct device* controller; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct omap2430_glue* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap2430_low_level_exit (struct musb*) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap2430_musb_exit(struct musb *musb)
{
	struct device *dev = musb->controller;
	struct omap2430_glue *glue = dev_get_drvdata(dev->parent);

	omap2430_low_level_exit(musb);
	phy_power_off(musb->phy);
	phy_exit(musb->phy);
	musb->phy = NULL;
	cancel_work_sync(&glue->omap_musb_mailbox_work);

	return 0;
}