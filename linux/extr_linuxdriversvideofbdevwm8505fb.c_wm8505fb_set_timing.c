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
struct wm8505fb_info {scalar_t__ regbase; } ;
struct TYPE_2__ {int left_margin; int xres; int right_margin; int hsync_len; int upper_margin; int yres; int lower_margin; int vsync_len; } ;
struct fb_info {TYPE_1__ var; } ;

/* Variables and functions */
 scalar_t__ WMT_GOVR_TG ; 
 scalar_t__ WMT_GOVR_TIMING_H_ALL ; 
 scalar_t__ WMT_GOVR_TIMING_H_END ; 
 scalar_t__ WMT_GOVR_TIMING_H_START ; 
 scalar_t__ WMT_GOVR_TIMING_H_SYNC ; 
 scalar_t__ WMT_GOVR_TIMING_V_ALL ; 
 scalar_t__ WMT_GOVR_TIMING_V_END ; 
 scalar_t__ WMT_GOVR_TIMING_V_START ; 
 scalar_t__ WMT_GOVR_TIMING_V_SYNC ; 
 struct wm8505fb_info* to_wm8505fb_info (struct fb_info*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int wm8505fb_set_timing(struct fb_info *info)
{
	struct wm8505fb_info *fbi = to_wm8505fb_info(info);

	int h_start = info->var.left_margin;
	int h_end = h_start + info->var.xres;
	int h_all = h_end + info->var.right_margin;
	int h_sync = info->var.hsync_len;

	int v_start = info->var.upper_margin;
	int v_end = v_start + info->var.yres;
	int v_all = v_end + info->var.lower_margin;
	int v_sync = info->var.vsync_len;

	writel(0, fbi->regbase + WMT_GOVR_TG);

	writel(h_start, fbi->regbase + WMT_GOVR_TIMING_H_START);
	writel(h_end,   fbi->regbase + WMT_GOVR_TIMING_H_END);
	writel(h_all,   fbi->regbase + WMT_GOVR_TIMING_H_ALL);
	writel(h_sync,  fbi->regbase + WMT_GOVR_TIMING_H_SYNC);

	writel(v_start, fbi->regbase + WMT_GOVR_TIMING_V_START);
	writel(v_end,   fbi->regbase + WMT_GOVR_TIMING_V_END);
	writel(v_all,   fbi->regbase + WMT_GOVR_TIMING_V_ALL);
	writel(v_sync,  fbi->regbase + WMT_GOVR_TIMING_V_SYNC);

	writel(1, fbi->regbase + WMT_GOVR_TG);

	return 0;
}