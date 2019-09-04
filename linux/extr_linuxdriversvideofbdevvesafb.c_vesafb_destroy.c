#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vesafb_par {int /*<<< orphan*/  wc_cookie; } ;
struct fb_info {TYPE_1__* apertures; scalar_t__ screen_base; int /*<<< orphan*/  cmap; struct vesafb_par* par; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;
struct TYPE_3__ {TYPE_2__* ranges; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vesafb_destroy(struct fb_info *info)
{
	struct vesafb_par *par = info->par;

	fb_dealloc_cmap(&info->cmap);
	arch_phys_wc_del(par->wc_cookie);
	if (info->screen_base)
		iounmap(info->screen_base);
	release_mem_region(info->apertures->ranges[0].base, info->apertures->ranges[0].size);
}