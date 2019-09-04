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
struct mx3fb_info {int /*<<< orphan*/  mutex; int /*<<< orphan*/  pseudo_palette; scalar_t__ cur_ipu_buf; int /*<<< orphan*/  cookie; } ;
struct fb_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  activate; } ;
struct fb_info {int /*<<< orphan*/  cmap; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/  flags; struct fb_ops* fbops; TYPE_1__ var; struct mx3fb_info* par; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FBINFO_FLAG_DEFAULT ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct fb_info* framebuffer_alloc (int,struct device*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct fb_info *mx3fb_init_fbinfo(struct device *dev, struct fb_ops *ops)
{
	struct fb_info *fbi;
	struct mx3fb_info *mx3fbi;
	int ret;

	/* Allocate sufficient memory for the fb structure */
	fbi = framebuffer_alloc(sizeof(struct mx3fb_info), dev);
	if (!fbi)
		return NULL;

	mx3fbi			= fbi->par;
	mx3fbi->cookie		= -EINVAL;
	mx3fbi->cur_ipu_buf	= 0;

	fbi->var.activate	= FB_ACTIVATE_NOW;

	fbi->fbops		= ops;
	fbi->flags		= FBINFO_FLAG_DEFAULT;
	fbi->pseudo_palette	= mx3fbi->pseudo_palette;

	mutex_init(&mx3fbi->mutex);

	/* Allocate colormap */
	ret = fb_alloc_cmap(&fbi->cmap, 16, 0);
	if (ret < 0) {
		framebuffer_release(fbi);
		return NULL;
	}

	return fbi;
}