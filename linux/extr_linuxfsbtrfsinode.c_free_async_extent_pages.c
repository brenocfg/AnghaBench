#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct async_extent {int nr_pages; TYPE_1__** pages; } ;
struct TYPE_3__ {int /*<<< orphan*/  mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__**) ; 
 int /*<<< orphan*/  put_page (TYPE_1__*) ; 

__attribute__((used)) static void free_async_extent_pages(struct async_extent *async_extent)
{
	int i;

	if (!async_extent->pages)
		return;

	for (i = 0; i < async_extent->nr_pages; i++) {
		WARN_ON(async_extent->pages[i]->mapping);
		put_page(async_extent->pages[i]);
	}
	kfree(async_extent->pages);
	async_extent->nr_pages = 0;
	async_extent->pages = NULL;
}