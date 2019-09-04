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
struct xfs_mru_cache {struct xfs_mru_cache* lists; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (struct xfs_mru_cache*) ; 
 int /*<<< orphan*/  xfs_mru_cache_flush (struct xfs_mru_cache*) ; 

void
xfs_mru_cache_destroy(
	struct xfs_mru_cache	*mru)
{
	if (!mru || !mru->lists)
		return;

	xfs_mru_cache_flush(mru);

	kmem_free(mru->lists);
	kmem_free(mru);
}