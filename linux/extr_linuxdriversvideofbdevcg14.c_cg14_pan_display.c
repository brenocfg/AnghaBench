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
struct fb_var_screeninfo {scalar_t__ vmode; scalar_t__ yoffset; scalar_t__ xoffset; } ;
struct fb_info {scalar_t__ par; } ;
struct cg14_par {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __cg14_reset (struct cg14_par*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cg14_pan_display(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct cg14_par *par = (struct cg14_par *) info->par;
	unsigned long flags;

	/* We just use this to catch switches out of
	 * graphics mode.
	 */
	spin_lock_irqsave(&par->lock, flags);
	__cg14_reset(par);
	spin_unlock_irqrestore(&par->lock, flags);

	if (var->xoffset || var->yoffset || var->vmode)
		return -EINVAL;
	return 0;
}