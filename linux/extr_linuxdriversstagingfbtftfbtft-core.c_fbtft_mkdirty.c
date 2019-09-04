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
struct fbtft_par {int dirty_lines_start; int dirty_lines_end; int /*<<< orphan*/  dirty_lock; } ;
struct TYPE_2__ {int yres; } ;
struct fb_info {int /*<<< orphan*/  deferred_work; TYPE_1__ var; struct fb_deferred_io* fbdefio; struct fbtft_par* par; } ;
struct fb_deferred_io {int /*<<< orphan*/  delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fbtft_mkdirty(struct fb_info *info, int y, int height)
{
	struct fbtft_par *par = info->par;
	struct fb_deferred_io *fbdefio = info->fbdefio;

	/* special case, needed ? */
	if (y == -1) {
		y = 0;
		height = info->var.yres - 1;
	}

	/* Mark display lines/area as dirty */
	spin_lock(&par->dirty_lock);
	if (y < par->dirty_lines_start)
		par->dirty_lines_start = y;
	if (y + height - 1 > par->dirty_lines_end)
		par->dirty_lines_end = y + height - 1;
	spin_unlock(&par->dirty_lock);

	/* Schedule deferred_io to update display (no-op if already on queue)*/
	schedule_delayed_work(&info->deferred_work, fbdefio->delay);
}