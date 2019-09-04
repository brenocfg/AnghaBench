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
struct mmpfb_info {int /*<<< orphan*/  path; int /*<<< orphan*/  mode; int /*<<< orphan*/  output_fmt; int /*<<< orphan*/  dev; struct fb_info* fb_info; } ;
struct mmp_mode {int /*<<< orphan*/  pix_fmt_out; } ;
struct fb_videomode {int dummy; } ;
struct fb_info {int /*<<< orphan*/  var; int /*<<< orphan*/  modelist; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fb_videomode_to_modelist (struct fb_videomode*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_videomode_to_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct fb_videomode* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fb_videomode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct fb_videomode*,int) ; 
 int mmp_path_get_modelist (int /*<<< orphan*/ ,struct mmp_mode**) ; 
 int /*<<< orphan*/  mmp_path_set_mode (int /*<<< orphan*/ ,struct mmp_mode*) ; 
 int /*<<< orphan*/  mmpmode_to_fbmode (struct fb_videomode*,struct mmp_mode*) ; 

__attribute__((used)) static int modes_setup(struct mmpfb_info *fbi)
{
	struct fb_videomode *videomodes;
	struct mmp_mode *mmp_modes;
	struct fb_info *info = fbi->fb_info;
	int videomode_num, i;

	/* get videomodes from path */
	videomode_num = mmp_path_get_modelist(fbi->path, &mmp_modes);
	if (!videomode_num) {
		dev_warn(fbi->dev, "can't get videomode num\n");
		return 0;
	}
	/* put videomode list to info structure */
	videomodes = kcalloc(videomode_num, sizeof(struct fb_videomode),
			     GFP_KERNEL);
	if (!videomodes)
		return -ENOMEM;

	for (i = 0; i < videomode_num; i++)
		mmpmode_to_fbmode(&videomodes[i], &mmp_modes[i]);
	fb_videomode_to_modelist(videomodes, videomode_num, &info->modelist);

	/* set videomode[0] as default mode */
	memcpy(&fbi->mode, &videomodes[0], sizeof(struct fb_videomode));
	fbi->output_fmt = mmp_modes[0].pix_fmt_out;
	fb_videomode_to_var(&info->var, &fbi->mode);
	mmp_path_set_mode(fbi->path, &mmp_modes[0]);

	kfree(videomodes);
	return videomode_num;
}