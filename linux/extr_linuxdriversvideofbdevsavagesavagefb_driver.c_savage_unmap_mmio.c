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
struct TYPE_2__ {int /*<<< orphan*/ * vbase; } ;
struct savagefb_par {TYPE_1__ mmio; } ;
struct fb_info {struct savagefb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  savage_disable_mmio (struct savagefb_par*) ; 

__attribute__((used)) static void savage_unmap_mmio(struct fb_info *info)
{
	struct savagefb_par *par = info->par;
	DBG("savage_unmap_mmio");

	savage_disable_mmio(par);

	if (par->mmio.vbase) {
		iounmap(par->mmio.vbase);
		par->mmio.vbase = NULL;
	}
}