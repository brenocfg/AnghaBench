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
struct hvfb_par {TYPE_1__* mem; } ;
struct fb_info {int /*<<< orphan*/  screen_base; struct hvfb_par* par; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_fb_size ; 
 int /*<<< orphan*/  vmbus_free_mmio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hvfb_putmem(struct fb_info *info)
{
	struct hvfb_par *par = info->par;

	iounmap(info->screen_base);
	vmbus_free_mmio(par->mem->start, screen_fb_size);
	par->mem = NULL;
}