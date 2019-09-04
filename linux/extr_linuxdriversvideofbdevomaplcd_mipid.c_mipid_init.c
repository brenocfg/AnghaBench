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
struct omapfb_device {int dummy; } ;
struct mipid_device {int /*<<< orphan*/  saved_bklight_level; scalar_t__ enabled; int /*<<< orphan*/  mutex; int /*<<< orphan*/  esd_work; struct omapfb_device* fbdev; } ;
struct lcd_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipid_esd_start_check (struct mipid_device*) ; 
 int /*<<< orphan*/  mipid_esd_work ; 
 int /*<<< orphan*/  mipid_get_bklight_level (struct lcd_panel*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ panel_enabled (struct mipid_device*) ; 
 struct mipid_device* to_mipid_device (struct lcd_panel*) ; 

__attribute__((used)) static int mipid_init(struct lcd_panel *panel,
			    struct omapfb_device *fbdev)
{
	struct mipid_device *md = to_mipid_device(panel);

	md->fbdev = fbdev;
	INIT_DELAYED_WORK(&md->esd_work, mipid_esd_work);
	mutex_init(&md->mutex);

	md->enabled = panel_enabled(md);

	if (md->enabled)
		mipid_esd_start_check(md);
	else
		md->saved_bklight_level = mipid_get_bklight_level(panel);

	return 0;
}