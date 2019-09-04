#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  adapter; scalar_t__ par; } ;
struct savagefb_par {TYPE_1__ chan; } ;
struct fb_info {int /*<<< orphan*/  device; struct savagefb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDID_LENGTH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * fb_ddc_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fb_firmware_edid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int savagefb_probe_i2c_connector(struct fb_info *info, u8 **out_edid)
{
	struct savagefb_par *par = info->par;
	u8 *edid;

	if (par->chan.par)
		edid = fb_ddc_read(&par->chan.adapter);
	else
		edid = NULL;

	if (!edid) {
		/* try to get from firmware */
		const u8 *e = fb_firmware_edid(info->device);

		if (e)
			edid = kmemdup(e, EDID_LENGTH, GFP_KERNEL);
	}

	*out_edid = edid;

	return (edid) ? 0 : 1;
}