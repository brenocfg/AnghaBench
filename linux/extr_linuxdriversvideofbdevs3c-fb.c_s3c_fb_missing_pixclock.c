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
typedef  unsigned long long u64 ;
typedef  int u32 ;
struct fb_videomode {int left_margin; int hsync_len; int right_margin; int xres; int upper_margin; int vsync_len; int lower_margin; int yres; unsigned long long pixclock; scalar_t__ refresh; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 

__attribute__((used)) static void s3c_fb_missing_pixclock(struct fb_videomode *mode)
{
	u64 pixclk = 1000000000000ULL;
	u32 div;

	div  = mode->left_margin + mode->hsync_len + mode->right_margin +
	       mode->xres;
	div *= mode->upper_margin + mode->vsync_len + mode->lower_margin +
	       mode->yres;
	div *= mode->refresh ? : 60;

	do_div(pixclk, div);

	mode->pixclock = pixclk;
}