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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct lxfb_par {scalar_t__ vp_regs; scalar_t__ dc_regs; scalar_t__ gp_regs; int /*<<< orphan*/  output; } ;
struct fb_videomode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; int /*<<< orphan*/  smem_len; } ;
struct fb_info {int /*<<< orphan*/  cmap; scalar_t__ screen_base; TYPE_1__ fix; int /*<<< orphan*/  var; struct lxfb_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OUTPUT_CRT ; 
 int /*<<< orphan*/  OUTPUT_PANEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int fb_find_mode (int /*<<< orphan*/ *,struct fb_info*,int /*<<< orphan*/ ,struct fb_videomode*,unsigned int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fb_info (struct fb_info*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  get_modedb (struct fb_videomode**,unsigned int*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  lxfb_check_var (int /*<<< orphan*/ *,struct fb_info*) ; 
 struct fb_info* lxfb_init_fbinfo (int /*<<< orphan*/ *) ; 
 int lxfb_map_video_memory (struct fb_info*,struct pci_dev*) ; 
 int /*<<< orphan*/  lxfb_set_par (struct fb_info*) ; 
 int /*<<< orphan*/  memset_io (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode_option ; 
 int /*<<< orphan*/  noclear ; 
 scalar_t__ nocrt ; 
 scalar_t__ nopanel ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct fb_info*) ; 
 int /*<<< orphan*/  pm_set_vt_switch (int /*<<< orphan*/ ) ; 
 scalar_t__ register_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  vt_switch ; 

__attribute__((used)) static int lxfb_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct lxfb_par *par;
	struct fb_info *info;
	int ret;

	struct fb_videomode *modedb_ptr;
	unsigned int modedb_size;

	info = lxfb_init_fbinfo(&pdev->dev);

	if (info == NULL)
		return -ENOMEM;

	par = info->par;

	ret = lxfb_map_video_memory(info, pdev);

	if (ret < 0) {
		dev_err(&pdev->dev,
			"failed to map frame buffer or controller registers\n");
		goto err;
	}

	/* Set up the desired outputs */

	par->output = 0;
	par->output |= (nopanel) ? 0 : OUTPUT_PANEL;
	par->output |= (nocrt) ? 0 : OUTPUT_CRT;

	/* Set up the mode database */

	get_modedb(&modedb_ptr, &modedb_size);
	ret = fb_find_mode(&info->var, info, mode_option,
			   modedb_ptr, modedb_size, NULL, 16);

	if (ret == 0 || ret == 4) {
		dev_err(&pdev->dev, "could not find valid video mode\n");
		ret = -EINVAL;
		goto err;
	}

	/* Clear the screen of garbage, unless noclear was specified,
	 * in which case we assume the user knows what he is doing */

	if (!noclear)
		memset_io(info->screen_base, 0, info->fix.smem_len);

	/* Set the mode */

	lxfb_check_var(&info->var, info);
	lxfb_set_par(info);

	pm_set_vt_switch(vt_switch);

	if (register_framebuffer(info) < 0) {
		ret = -EINVAL;
		goto err;
	}
	pci_set_drvdata(pdev, info);
	fb_info(info, "%s frame buffer device\n", info->fix.id);

	return 0;

err:
	if (info->screen_base) {
		iounmap(info->screen_base);
		pci_release_region(pdev, 0);
	}
	if (par->gp_regs) {
		iounmap(par->gp_regs);
		pci_release_region(pdev, 1);
	}
	if (par->dc_regs) {
		iounmap(par->dc_regs);
		pci_release_region(pdev, 2);
	}
	if (par->vp_regs) {
		iounmap(par->vp_regs);
		pci_release_region(pdev, 3);
	}

	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);

	return ret;
}