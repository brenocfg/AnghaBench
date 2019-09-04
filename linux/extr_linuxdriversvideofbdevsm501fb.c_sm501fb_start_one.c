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
struct sm501fb_info {int /*<<< orphan*/  dev; struct fb_info** fb; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct fb_info {TYPE_1__ fix; int /*<<< orphan*/  node; int /*<<< orphan*/  mm_lock; } ;
typedef  enum sm501_controller { ____Placeholder_sm501_controller } sm501_controller ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int register_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  sm501_free_init_fb (struct sm501fb_info*,int) ; 
 int sm501fb_init_fb (struct fb_info*,int,char const*) ; 

__attribute__((used)) static int sm501fb_start_one(struct sm501fb_info *info,
			     enum sm501_controller head, const char *drvname)
{
	struct fb_info *fbi = info->fb[head];
	int ret;

	if (!fbi)
		return 0;

	mutex_init(&info->fb[head]->mm_lock);

	ret = sm501fb_init_fb(info->fb[head], head, drvname);
	if (ret) {
		dev_err(info->dev, "cannot initialise fb %s\n", drvname);
		return ret;
	}

	ret = register_framebuffer(info->fb[head]);
	if (ret) {
		dev_err(info->dev, "failed to register fb %s\n", drvname);
		sm501_free_init_fb(info, head);
		return ret;
	}

	dev_info(info->dev, "fb%d: %s frame buffer\n", fbi->node, fbi->fix.id);

	return 0;
}