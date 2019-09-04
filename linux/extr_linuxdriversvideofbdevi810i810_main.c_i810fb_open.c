#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vgastate {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  vgabase; int /*<<< orphan*/  flags; } ;
struct i810fb_par {scalar_t__ use_count; int /*<<< orphan*/  open_lock; TYPE_1__ state; int /*<<< orphan*/  mmio_start_virtual; } ;
struct fb_info {struct i810fb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_SAVE_CMAP ; 
 int /*<<< orphan*/  i810_save_vga_state (struct i810fb_par*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_vga (TYPE_1__*) ; 

__attribute__((used)) static int i810fb_open(struct fb_info *info, int user)
{
	struct i810fb_par *par = info->par;

	mutex_lock(&par->open_lock);
	if (par->use_count == 0) {
		memset(&par->state, 0, sizeof(struct vgastate));
		par->state.flags = VGA_SAVE_CMAP;
		par->state.vgabase = par->mmio_start_virtual;
		save_vga(&par->state);

		i810_save_vga_state(par);
	}

	par->use_count++;
	mutex_unlock(&par->open_lock);
	
	return 0;
}