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
struct mmpfb_info {int dummy; } ;
struct fb_info {struct mmpfb_info* par; } ;

/* Variables and functions */
 int FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  mmpfb_power (struct mmpfb_info*,int) ; 

__attribute__((used)) static int mmpfb_blank(int blank, struct fb_info *info)
{
	struct mmpfb_info *fbi = info->par;

	mmpfb_power(fbi, (blank == FB_BLANK_UNBLANK));

	return 0;
}