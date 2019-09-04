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
struct vga16fb_par {int ref_count; int /*<<< orphan*/  state; } ;
struct fb_info {struct vga16fb_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  restore_vga (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vga16fb_release(struct fb_info *info, int user)
{
	struct vga16fb_par *par = info->par;

	if (!par->ref_count)
		return -EINVAL;

	if (par->ref_count == 1)
		restore_vga(&par->state);
	par->ref_count--;

	return 0;
}