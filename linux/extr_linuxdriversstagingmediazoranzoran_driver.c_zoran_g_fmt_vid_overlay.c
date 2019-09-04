#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int width; int /*<<< orphan*/  height; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct zoran_fh {TYPE_2__ overlay_settings; struct zoran* zr; } ;
struct zoran {int dummy; } ;
struct TYPE_5__ {int width; int /*<<< orphan*/  height; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_7__ {int /*<<< orphan*/  field; TYPE_1__ w; } ;
struct TYPE_8__ {TYPE_3__ win; } ;
struct v4l2_format {TYPE_4__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int BUZ_MAX_HEIGHT ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_TOP ; 

__attribute__((used)) static int zoran_g_fmt_vid_overlay(struct file *file, void *__fh,
					struct v4l2_format *fmt)
{
	struct zoran_fh *fh = __fh;
	struct zoran *zr = fh->zr;

	fmt->fmt.win.w.left = fh->overlay_settings.x;
	fmt->fmt.win.w.top = fh->overlay_settings.y;
	fmt->fmt.win.w.width = fh->overlay_settings.width;
	fmt->fmt.win.w.height = fh->overlay_settings.height;
	if (fh->overlay_settings.width * 2 > BUZ_MAX_HEIGHT)
		fmt->fmt.win.field = V4L2_FIELD_INTERLACED;
	else
		fmt->fmt.win.field = V4L2_FIELD_TOP;

	return 0;
}