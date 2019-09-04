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
typedef  int xfs_dir2_db_t ;
struct xfs_da_geometry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DIR2_FREE_OFFSET ; 
 int xfs_dir2_byte_to_db (struct xfs_da_geometry*,int /*<<< orphan*/ ) ; 
 int xfs_dir2_free_max_bests (struct xfs_da_geometry*) ; 

__attribute__((used)) static xfs_dir2_db_t
xfs_dir2_db_to_fdb(struct xfs_da_geometry *geo, xfs_dir2_db_t db)
{
	return xfs_dir2_byte_to_db(geo, XFS_DIR2_FREE_OFFSET) +
			(db / xfs_dir2_free_max_bests(geo));
}