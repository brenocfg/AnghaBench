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
struct omapfb_update_window {int dummy; } ;
struct omapfb_plane_struct {int /*<<< orphan*/  fbdev; } ;
struct fb_info {struct omapfb_plane_struct* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  omapfb_rqueue_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapfb_rqueue_unlock (int /*<<< orphan*/ ) ; 
 int omapfb_update_window_async (struct fb_info*,struct omapfb_update_window*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omapfb_update_win(struct fb_info *fbi,
				struct omapfb_update_window *win)
{
	struct omapfb_plane_struct *plane = fbi->par;
	int ret;

	omapfb_rqueue_lock(plane->fbdev);
	ret = omapfb_update_window_async(fbi, win, NULL, NULL);
	omapfb_rqueue_unlock(plane->fbdev);

	return ret;
}