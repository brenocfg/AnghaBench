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
typedef  void* xfs_agino_t ;
struct xfs_perag {int /*<<< orphan*/  pag_mount; } ;
struct xfs_iunlink {void* iu_next_unlinked; void* iu_agino; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_NOFS ; 
 int /*<<< orphan*/  XFS_ERRTAG_IUNLINK_FALLBACK ; 
 scalar_t__ XFS_TEST_ERROR (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xfs_iunlink* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int xfs_iunlink_insert_backref (struct xfs_perag*,struct xfs_iunlink*) ; 

__attribute__((used)) static int
xfs_iunlink_add_backref(
	struct xfs_perag	*pag,
	xfs_agino_t		prev_agino,
	xfs_agino_t		this_agino)
{
	struct xfs_iunlink	*iu;

	if (XFS_TEST_ERROR(false, pag->pag_mount, XFS_ERRTAG_IUNLINK_FALLBACK))
		return 0;

	iu = kmem_zalloc(sizeof(*iu), KM_NOFS);
	iu->iu_agino = prev_agino;
	iu->iu_next_unlinked = this_agino;

	return xfs_iunlink_insert_backref(pag, iu);
}