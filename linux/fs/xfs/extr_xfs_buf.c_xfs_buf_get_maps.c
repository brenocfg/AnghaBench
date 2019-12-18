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
struct xfs_buf_map {int dummy; } ;
struct xfs_buf {int b_map_count; int /*<<< orphan*/ * b_maps; int /*<<< orphan*/  __b_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KM_NOFS ; 
 int /*<<< orphan*/ * kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xfs_buf_get_maps(
	struct xfs_buf		*bp,
	int			map_count)
{
	ASSERT(bp->b_maps == NULL);
	bp->b_map_count = map_count;

	if (map_count == 1) {
		bp->b_maps = &bp->__b_map;
		return 0;
	}

	bp->b_maps = kmem_zalloc(map_count * sizeof(struct xfs_buf_map),
				KM_NOFS);
	if (!bp->b_maps)
		return -ENOMEM;
	return 0;
}