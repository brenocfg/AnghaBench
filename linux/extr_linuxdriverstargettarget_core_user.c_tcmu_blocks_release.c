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
struct radix_tree_root {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_db_count ; 
 struct page* radix_tree_delete (struct radix_tree_root*,int) ; 

__attribute__((used)) static void tcmu_blocks_release(struct radix_tree_root *blocks,
				int start, int end)
{
	int i;
	struct page *page;

	for (i = start; i < end; i++) {
		page = radix_tree_delete(blocks, i);
		if (page) {
			__free_page(page);
			atomic_dec(&global_db_count);
		}
	}
}