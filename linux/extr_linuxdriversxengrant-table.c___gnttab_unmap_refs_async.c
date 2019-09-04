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
struct gntab_unmap_queue_data {int count; int age; int /*<<< orphan*/  (* done ) (int,struct gntab_unmap_queue_data*) ;int /*<<< orphan*/ * pages; int /*<<< orphan*/  kunmap_ops; int /*<<< orphan*/  unmap_ops; int /*<<< orphan*/  gnttab_work; } ;

/* Variables and functions */
 int GNTTAB_UNMAP_REFS_DELAY ; 
 int gnttab_unmap_refs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int page_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,struct gntab_unmap_queue_data*) ; 

__attribute__((used)) static void __gnttab_unmap_refs_async(struct gntab_unmap_queue_data* item)
{
	int ret;
	int pc;

	for (pc = 0; pc < item->count; pc++) {
		if (page_count(item->pages[pc]) > 1) {
			unsigned long delay = GNTTAB_UNMAP_REFS_DELAY * (item->age + 1);
			schedule_delayed_work(&item->gnttab_work,
					      msecs_to_jiffies(delay));
			return;
		}
	}

	ret = gnttab_unmap_refs(item->unmap_ops, item->kunmap_ops,
				item->pages, item->count);
	item->done(ret, item);
}