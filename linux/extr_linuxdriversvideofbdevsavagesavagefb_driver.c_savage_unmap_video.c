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
struct TYPE_2__ {int /*<<< orphan*/ * vbase; int /*<<< orphan*/  wc_cookie; } ;
struct savagefb_par {TYPE_1__ video; } ;
struct fb_info {int /*<<< orphan*/ * screen_base; struct savagefb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void savage_unmap_video(struct fb_info *info)
{
	struct savagefb_par *par = info->par;

	DBG("savage_unmap_video");

	if (par->video.vbase) {
		arch_phys_wc_del(par->video.wc_cookie);
		iounmap(par->video.vbase);
		par->video.vbase = NULL;
		info->screen_base = NULL;
	}
}