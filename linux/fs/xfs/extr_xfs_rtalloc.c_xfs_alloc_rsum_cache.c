#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  m_rsum_cache; } ;
typedef  TYPE_1__ xfs_mount_t ;
typedef  int /*<<< orphan*/  xfs_extlen_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_zalloc_large (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_warn (TYPE_1__*,char*) ; 

__attribute__((used)) static void
xfs_alloc_rsum_cache(
	xfs_mount_t	*mp,		/* file system mount structure */
	xfs_extlen_t	rbmblocks)	/* number of rt bitmap blocks */
{
	/*
	 * The rsum cache is initialized to all zeroes, which is trivially a
	 * lower bound on the minimum level with any free extents. We can
	 * continue without the cache if it couldn't be allocated.
	 */
	mp->m_rsum_cache = kmem_zalloc_large(rbmblocks, 0);
	if (!mp->m_rsum_cache)
		xfs_warn(mp, "could not allocate realtime summary cache");
}