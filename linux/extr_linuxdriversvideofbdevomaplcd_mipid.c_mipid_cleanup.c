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
struct mipid_device {scalar_t__ enabled; } ;
struct lcd_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mipid_esd_stop_check (struct mipid_device*) ; 
 struct mipid_device* to_mipid_device (struct lcd_panel*) ; 

__attribute__((used)) static void mipid_cleanup(struct lcd_panel *panel)
{
	struct mipid_device *md = to_mipid_device(panel);

	if (md->enabled)
		mipid_esd_stop_check(md);
}