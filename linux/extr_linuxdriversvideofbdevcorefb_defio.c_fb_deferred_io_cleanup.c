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
struct page {int /*<<< orphan*/ * mapping; } ;
struct TYPE_4__ {int smem_len; } ;
struct fb_info {TYPE_1__* fbops; TYPE_2__ fix; int /*<<< orphan*/  deferred_work; struct fb_deferred_io* fbdefio; } ;
struct fb_deferred_io {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fb_mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct page* fb_deferred_io_page (struct fb_info*,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void fb_deferred_io_cleanup(struct fb_info *info)
{
	struct fb_deferred_io *fbdefio = info->fbdefio;
	struct page *page;
	int i;

	BUG_ON(!fbdefio);
	cancel_delayed_work_sync(&info->deferred_work);

	/* clear out the mapping that we setup */
	for (i = 0 ; i < info->fix.smem_len; i += PAGE_SIZE) {
		page = fb_deferred_io_page(info, i);
		page->mapping = NULL;
	}

	info->fbops->fb_mmap = NULL;
	mutex_destroy(&fbdefio->lock);
}