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
struct tcx_par {int /*<<< orphan*/  lock; } ;
struct fb_info {scalar_t__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tcx_set_control_plane (struct fb_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void tcx_reset(struct fb_info *info)
{
	struct tcx_par *par = (struct tcx_par *) info->par;
	unsigned long flags;

	spin_lock_irqsave(&par->lock, flags);
	__tcx_set_control_plane(info);
	spin_unlock_irqrestore(&par->lock, flags);
}