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
struct page {int dummy; } ;
struct mdev_state {struct page** pages; int /*<<< orphan*/  ops_lock; } ;
typedef  size_t pgoff_t ;

/* Variables and functions */
 int GFP_HIGHUSER ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __GFP_ZERO ; 
 struct page* alloc_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *__mbochs_get_page(struct mdev_state *mdev_state,
				      pgoff_t pgoff)
{
	WARN_ON(!mutex_is_locked(&mdev_state->ops_lock));

	if (!mdev_state->pages[pgoff]) {
		mdev_state->pages[pgoff] =
			alloc_pages(GFP_HIGHUSER | __GFP_ZERO, 0);
		if (!mdev_state->pages[pgoff])
			return NULL;
	}

	get_page(mdev_state->pages[pgoff]);
	return mdev_state->pages[pgoff];
}