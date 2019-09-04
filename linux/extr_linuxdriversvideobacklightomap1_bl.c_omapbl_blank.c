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
struct omap_backlight {int /*<<< orphan*/  current_intensity; int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_power ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  omapbl_send_enable (int) ; 
 int /*<<< orphan*/  omapbl_send_intensity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void omapbl_blank(struct omap_backlight *bl, int mode)
{
	if (bl->pdata->set_power)
		bl->pdata->set_power(bl->dev, mode);

	switch (mode) {
	case FB_BLANK_NORMAL:
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_POWERDOWN:
		omapbl_send_intensity(0);
		omapbl_send_enable(0);
		break;

	case FB_BLANK_UNBLANK:
		omapbl_send_intensity(bl->current_intensity);
		omapbl_send_enable(1);
		break;
	}
}