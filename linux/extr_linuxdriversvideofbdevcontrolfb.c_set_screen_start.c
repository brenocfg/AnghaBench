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
struct fb_par_control {int xoffset; int yoffset; int pitch; int cmode; } ;
struct fb_info_control {struct fb_par_control par; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTRL_REG (struct fb_info_control*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  start_addr ; 

__attribute__((used)) static inline void set_screen_start(int xoffset, int yoffset,
	struct fb_info_control *p)
{
	struct fb_par_control *par = &p->par;

	par->xoffset = xoffset;
	par->yoffset = yoffset;
	out_le32(CNTRL_REG(p,start_addr),
		 par->yoffset * par->pitch + (par->xoffset << par->cmode));
}