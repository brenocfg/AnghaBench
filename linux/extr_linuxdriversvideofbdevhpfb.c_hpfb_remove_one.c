#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  start; } ;
struct dio_dev {scalar_t__ scode; TYPE_2__ resource; } ;
struct TYPE_4__ {void* screen_base; int /*<<< orphan*/  cmap; } ;

/* Variables and functions */
 scalar_t__ DIOII_SCBASE ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 TYPE_1__ fb_info ; 
 scalar_t__ fb_regs ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_2__*) ; 
 int /*<<< orphan*/  unregister_framebuffer (TYPE_1__*) ; 

__attribute__((used)) static void hpfb_remove_one(struct dio_dev *d)
{
	unregister_framebuffer(&fb_info);
	if (d->scode >= DIOII_SCBASE)
		iounmap((void *)fb_regs);
	release_mem_region(d->resource.start, resource_size(&d->resource));
	fb_dealloc_cmap(&fb_info.cmap);
	if (fb_info.screen_base)
		iounmap(fb_info.screen_base);
}