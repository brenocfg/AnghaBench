#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
typedef  int /*<<< orphan*/  xfs_dablk_t ;
struct xfs_mount {int /*<<< orphan*/  m_sb; int /*<<< orphan*/  m_dir_geo; } ;
struct xfs_inode {TYPE_1__* d_ops; struct xfs_mount* i_mount; } ;
struct xfs_dir3_free_hdr {int /*<<< orphan*/  nused; int /*<<< orphan*/  nvalid; int /*<<< orphan*/  firstdb; } ;
struct xfs_dir2_free_hdr {int /*<<< orphan*/  nused; int /*<<< orphan*/  nvalid; int /*<<< orphan*/  firstdb; } ;
struct xfs_buf {struct xfs_dir3_free_hdr* b_addr; } ;
struct TYPE_2__ {int (* free_max_bests ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DIR2_FREE_OFFSET ; 
 int /*<<< orphan*/ * __this_address ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int xfs_dir2_byte_to_db (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_dir2_da_to_db (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_sb_version_hascrc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static xfs_failaddr_t
xfs_dir3_free_header_check(
	struct xfs_inode	*dp,
	xfs_dablk_t		fbno,
	struct xfs_buf		*bp)
{
	struct xfs_mount	*mp = dp->i_mount;
	unsigned int		firstdb;
	int			maxbests;

	maxbests = dp->d_ops->free_max_bests(mp->m_dir_geo);
	firstdb = (xfs_dir2_da_to_db(mp->m_dir_geo, fbno) -
		   xfs_dir2_byte_to_db(mp->m_dir_geo, XFS_DIR2_FREE_OFFSET)) *
			maxbests;
	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		struct xfs_dir3_free_hdr *hdr3 = bp->b_addr;

		if (be32_to_cpu(hdr3->firstdb) != firstdb)
			return __this_address;
		if (be32_to_cpu(hdr3->nvalid) > maxbests)
			return __this_address;
		if (be32_to_cpu(hdr3->nvalid) < be32_to_cpu(hdr3->nused))
			return __this_address;
	} else {
		struct xfs_dir2_free_hdr *hdr = bp->b_addr;

		if (be32_to_cpu(hdr->firstdb) != firstdb)
			return __this_address;
		if (be32_to_cpu(hdr->nvalid) > maxbests)
			return __this_address;
		if (be32_to_cpu(hdr->nvalid) < be32_to_cpu(hdr->nused))
			return __this_address;
	}
	return NULL;
}