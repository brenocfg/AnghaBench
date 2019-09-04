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
struct TYPE_2__ {unsigned long smem_start; } ;
struct fb_info {int /*<<< orphan*/  cmap; int /*<<< orphan*/  flags; int /*<<< orphan*/ * fbops; int /*<<< orphan*/  var; TYPE_1__ fix; int /*<<< orphan*/  screen_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBINFO_DEFAULT ; 
 int /*<<< orphan*/  chips_hw_init () ; 
 TYPE_1__ chipsfb_fix ; 
 int /*<<< orphan*/  chipsfb_ops ; 
 int /*<<< orphan*/  chipsfb_var ; 
 int /*<<< orphan*/  fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_chips(struct fb_info *p, unsigned long addr)
{
	memset(p->screen_base, 0, 0x100000);

	p->fix = chipsfb_fix;
	p->fix.smem_start = addr;

	p->var = chipsfb_var;

	p->fbops = &chipsfb_ops;
	p->flags = FBINFO_DEFAULT;

	fb_alloc_cmap(&p->cmap, 256, 0);

	chips_hw_init();
}