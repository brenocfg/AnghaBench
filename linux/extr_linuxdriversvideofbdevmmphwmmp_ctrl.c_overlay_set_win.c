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
struct mmp_win {int* pitch; int ysrc; int xsrc; int ydst; int xdst; int ypos; int xpos; } ;
struct mmp_overlay {int /*<<< orphan*/  access_ok; int /*<<< orphan*/  win; int /*<<< orphan*/  path; } ;
struct lcd_regs {int /*<<< orphan*/  g_start; int /*<<< orphan*/  g_size_z; int /*<<< orphan*/  g_size; int /*<<< orphan*/  g_pitch; int /*<<< orphan*/  v_start; int /*<<< orphan*/  v_size_z; int /*<<< orphan*/  v_size; int /*<<< orphan*/  v_pitch_uv; int /*<<< orphan*/  v_pitch_yc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmafetch_set_fmt (struct mmp_overlay*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mmp_win*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ overlay_is_vid (struct mmp_overlay*) ; 
 struct lcd_regs* path_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void overlay_set_win(struct mmp_overlay *overlay, struct mmp_win *win)
{
	struct lcd_regs *regs = path_regs(overlay->path);

	/* assert win supported */
	memcpy(&overlay->win, win, sizeof(struct mmp_win));

	mutex_lock(&overlay->access_ok);

	if (overlay_is_vid(overlay)) {
		writel_relaxed(win->pitch[0], &regs->v_pitch_yc);
		writel_relaxed(win->pitch[2] << 16 |
				win->pitch[1], &regs->v_pitch_uv);

		writel_relaxed((win->ysrc << 16) | win->xsrc, &regs->v_size);
		writel_relaxed((win->ydst << 16) | win->xdst, &regs->v_size_z);
		writel_relaxed(win->ypos << 16 | win->xpos, &regs->v_start);
	} else {
		writel_relaxed(win->pitch[0], &regs->g_pitch);

		writel_relaxed((win->ysrc << 16) | win->xsrc, &regs->g_size);
		writel_relaxed((win->ydst << 16) | win->xdst, &regs->g_size_z);
		writel_relaxed(win->ypos << 16 | win->xpos, &regs->g_start);
	}

	dmafetch_set_fmt(overlay);
	mutex_unlock(&overlay->access_ok);
}