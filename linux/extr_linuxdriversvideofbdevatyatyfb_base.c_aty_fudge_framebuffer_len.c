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
struct TYPE_2__ {int smem_len; } ;
struct fb_info {TYPE_1__ fix; scalar_t__ par; } ;
struct atyfb_par {scalar_t__ bus_type; int /*<<< orphan*/  aux_start; } ;

/* Variables and functions */
 scalar_t__ GUI_RESERVE ; 
 scalar_t__ ISA ; 

__attribute__((used)) static void aty_fudge_framebuffer_len(struct fb_info *info)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;

	if (!par->aux_start &&
	    (info->fix.smem_len == 0x800000 ||
	     (par->bus_type == ISA && info->fix.smem_len == 0x400000)))
		info->fix.smem_len -= GUI_RESERVE;
}