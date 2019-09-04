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
struct nvidia_par {int /*<<< orphan*/  open_count; int /*<<< orphan*/  initial_state; } ;
struct fb_info {struct nvidia_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvidia_save_vga (struct nvidia_par*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_vga_x86 (struct nvidia_par*) ; 

__attribute__((used)) static int nvidiafb_open(struct fb_info *info, int user)
{
	struct nvidia_par *par = info->par;

	if (!par->open_count) {
		save_vga_x86(par);
		nvidia_save_vga(par, &par->initial_state);
	}

	par->open_count++;
	return 0;
}