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
struct fb_info {int dummy; } ;

/* Variables and functions */
#define  FB_BLANK_NORMAL 129 
#define  FB_BLANK_UNBLANK 128 
 int /*<<< orphan*/  gbe_loadcmap () ; 
 int /*<<< orphan*/  gbe_turn_off () ; 
 int /*<<< orphan*/  gbe_turn_on () ; 

__attribute__((used)) static int gbefb_blank(int blank, struct fb_info *info)
{
	/* 0 unblank, 1 blank, 2 no vsync, 3 no hsync, 4 off */
	switch (blank) {
	case FB_BLANK_UNBLANK:		/* unblank */
		gbe_turn_on();
		gbe_loadcmap();
		break;

	case FB_BLANK_NORMAL:		/* blank */
		gbe_turn_off();
		break;

	default:
		/* Nothing */
		break;
	}
	return 0;
}