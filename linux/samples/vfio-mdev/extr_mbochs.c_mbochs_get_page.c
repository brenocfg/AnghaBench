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
struct mdev_state {scalar_t__ pagecount; int /*<<< orphan*/  ops_lock; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct page* __mbochs_get_page (struct mdev_state*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *mbochs_get_page(struct mdev_state *mdev_state,
				    pgoff_t pgoff)
{
	struct page *page;

	if (WARN_ON(pgoff >= mdev_state->pagecount))
		return NULL;

	mutex_lock(&mdev_state->ops_lock);
	page = __mbochs_get_page(mdev_state, pgoff);
	mutex_unlock(&mdev_state->ops_lock);

	return page;
}