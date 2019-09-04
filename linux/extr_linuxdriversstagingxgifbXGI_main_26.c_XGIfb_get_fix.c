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
struct xgifb_video_info {int video_bpp; int /*<<< orphan*/  mmio_size; int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  video_linelength; int /*<<< orphan*/  video_size; int /*<<< orphan*/  video_base; } ;
struct fb_info {int /*<<< orphan*/  mm_lock; int /*<<< orphan*/  count; struct xgifb_video_info* par; } ;
struct fb_fix_screeninfo {int ypanstep; int /*<<< orphan*/  accel; int /*<<< orphan*/  mmio_len; int /*<<< orphan*/  mmio_start; int /*<<< orphan*/  line_length; scalar_t__ ywrapstep; scalar_t__ xpanstep; int /*<<< orphan*/  visual; scalar_t__ type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ACCEL_SIS_XABRE ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_DIRECTCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 scalar_t__ XGIfb_ypan ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct fb_fix_screeninfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int XGIfb_get_fix(struct fb_fix_screeninfo *fix, int con,
			 struct fb_info *info)
{
	struct xgifb_video_info *xgifb_info = info->par;

	memset(fix, 0, sizeof(struct fb_fix_screeninfo));

	strncpy(fix->id, "XGI", sizeof(fix->id) - 1);

	/* if register_framebuffer has been called, we must lock */
	if (atomic_read(&info->count))
		mutex_lock(&info->mm_lock);

	fix->smem_start = xgifb_info->video_base;
	fix->smem_len = xgifb_info->video_size;

	/* if register_framebuffer has been called, we can unlock */
	if (atomic_read(&info->count))
		mutex_unlock(&info->mm_lock);

	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->type_aux = 0;
	if (xgifb_info->video_bpp == 8)
		fix->visual = FB_VISUAL_PSEUDOCOLOR;
	else
		fix->visual = FB_VISUAL_DIRECTCOLOR;
	fix->xpanstep = 0;
	if (XGIfb_ypan)
		fix->ypanstep = 1;
	fix->ywrapstep = 0;
	fix->line_length = xgifb_info->video_linelength;
	fix->mmio_start = xgifb_info->mmio_base;
	fix->mmio_len = xgifb_info->mmio_size;
	fix->accel = FB_ACCEL_SIS_XABRE;

	return 0;
}