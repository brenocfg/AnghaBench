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
struct xfs_mru_cache_elem {int dummy; } ;
struct xfs_mru_cache {int /*<<< orphan*/  data; int /*<<< orphan*/  (* free_func ) (int /*<<< orphan*/ ,struct xfs_mru_cache_elem*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct xfs_mru_cache_elem*) ; 
 struct xfs_mru_cache_elem* xfs_mru_cache_remove (struct xfs_mru_cache*,unsigned long) ; 

void
xfs_mru_cache_delete(
	struct xfs_mru_cache	*mru,
	unsigned long		key)
{
	struct xfs_mru_cache_elem *elem;

	elem = xfs_mru_cache_remove(mru, key);
	if (elem)
		mru->free_func(mru->data, elem);
}