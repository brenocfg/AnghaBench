#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mxsfb_info {TYPE_1__* pdev; } ;
struct fb_videomode {int dummy; } ;
struct fb_var_screeninfo {int /*<<< orphan*/  vmode; scalar_t__ accel_flags; int /*<<< orphan*/  activate; scalar_t__ nonstd; } ;
struct TYPE_4__ {int ypanstep; unsigned int smem_len; int /*<<< orphan*/  smem_start; int /*<<< orphan*/  accel; int /*<<< orphan*/  visual; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct fb_info {int flags; unsigned int screen_size; TYPE_2__ fix; void* screen_base; int /*<<< orphan*/ * fbops; struct fb_var_screeninfo var; struct mxsfb_info* par; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FBINFO_FLAG_DEFAULT ; 
 int FBINFO_READS_FAST ; 
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_ALIGN (unsigned int) ; 
 unsigned int SZ_2M ; 
 void* dma_alloc_wc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int mxsfb_init_fbinfo_dt (struct fb_info*,struct fb_videomode*) ; 
 int /*<<< orphan*/  mxsfb_ops ; 
 scalar_t__ mxsfb_restore_mode (struct fb_info*,struct fb_videomode*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int mxsfb_init_fbinfo(struct fb_info *fb_info,
			struct fb_videomode *vmode)
{
	int ret;
	struct mxsfb_info *host = fb_info->par;
	struct device *dev = &host->pdev->dev;
	struct fb_var_screeninfo *var = &fb_info->var;
	dma_addr_t fb_phys;
	void *fb_virt;
	unsigned fb_size;

	fb_info->fbops = &mxsfb_ops;
	fb_info->flags = FBINFO_FLAG_DEFAULT | FBINFO_READS_FAST;
	strlcpy(fb_info->fix.id, "mxs", sizeof(fb_info->fix.id));
	fb_info->fix.type = FB_TYPE_PACKED_PIXELS;
	fb_info->fix.ypanstep = 1;
	fb_info->fix.visual = FB_VISUAL_TRUECOLOR,
	fb_info->fix.accel = FB_ACCEL_NONE;

	ret = mxsfb_init_fbinfo_dt(fb_info, vmode);
	if (ret)
		return ret;

	var->nonstd = 0;
	var->activate = FB_ACTIVATE_NOW;
	var->accel_flags = 0;
	var->vmode = FB_VMODE_NONINTERLACED;

	/* Memory allocation for framebuffer */
	fb_size = SZ_2M;
	fb_virt = dma_alloc_wc(dev, PAGE_ALIGN(fb_size), &fb_phys, GFP_KERNEL);
	if (!fb_virt)
		return -ENOMEM;

	fb_info->fix.smem_start = fb_phys;
	fb_info->screen_base = fb_virt;
	fb_info->screen_size = fb_info->fix.smem_len = fb_size;

	if (mxsfb_restore_mode(fb_info, vmode))
		memset(fb_virt, 0, fb_size);

	return 0;
}