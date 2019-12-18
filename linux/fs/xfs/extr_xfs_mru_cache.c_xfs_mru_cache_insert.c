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
struct xfs_mru_cache_elem {unsigned long key; int /*<<< orphan*/  list_node; } ;
struct xfs_mru_cache {int /*<<< orphan*/  lock; int /*<<< orphan*/  store; scalar_t__ lists; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _xfs_mru_cache_list_insert (struct xfs_mru_cache*,struct xfs_mru_cache_elem*) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,unsigned long,struct xfs_mru_cache_elem*) ; 
 scalar_t__ radix_tree_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int
xfs_mru_cache_insert(
	struct xfs_mru_cache	*mru,
	unsigned long		key,
	struct xfs_mru_cache_elem *elem)
{
	int			error;

	ASSERT(mru && mru->lists);
	if (!mru || !mru->lists)
		return -EINVAL;

	if (radix_tree_preload(GFP_NOFS))
		return -ENOMEM;

	INIT_LIST_HEAD(&elem->list_node);
	elem->key = key;

	spin_lock(&mru->lock);
	error = radix_tree_insert(&mru->store, key, elem);
	radix_tree_preload_end();
	if (!error)
		_xfs_mru_cache_list_insert(mru, elem);
	spin_unlock(&mru->lock);

	return error;
}