#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
struct TYPE_7__ {int /*<<< orphan*/  sb_meta_uuid; } ;
struct xfs_mount {TYPE_2__ m_sb; } ;
struct xfs_buf {TYPE_1__* b_pag; struct xfs_mount* b_mount; } ;
struct xfs_agf {int /*<<< orphan*/  agf_refcount_level; int /*<<< orphan*/  agf_length; int /*<<< orphan*/  agf_btreeblks; int /*<<< orphan*/  agf_seqno; int /*<<< orphan*/ * agf_levels; int /*<<< orphan*/  agf_flcount; int /*<<< orphan*/  agf_fllast; int /*<<< orphan*/  agf_flfirst; int /*<<< orphan*/  agf_freeblks; int /*<<< orphan*/  agf_versionnum; int /*<<< orphan*/  agf_magicnum; int /*<<< orphan*/  agf_lsn; int /*<<< orphan*/  agf_uuid; } ;
struct TYPE_6__ {int pag_agno; } ;

/* Variables and functions */
 scalar_t__ XFS_AGF_GOOD_VERSION (int) ; 
 size_t XFS_BTNUM_BNO ; 
 size_t XFS_BTNUM_CNT ; 
 size_t XFS_BTNUM_RMAP ; 
 int XFS_BTREE_MAXLEVELS ; 
 struct xfs_agf* XFS_BUF_TO_AGF (struct xfs_buf*) ; 
 int /*<<< orphan*/ * __this_address ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int xfs_agfl_size (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_log_check_lsn (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_sb_version_hascrc (TYPE_2__*) ; 
 scalar_t__ xfs_sb_version_haslazysbcount (TYPE_2__*) ; 
 scalar_t__ xfs_sb_version_hasreflink (TYPE_2__*) ; 
 scalar_t__ xfs_sb_version_hasrmapbt (TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_verify_magic (struct xfs_buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static xfs_failaddr_t
xfs_agf_verify(
	struct xfs_buf		*bp)
{
	struct xfs_mount	*mp = bp->b_mount;
	struct xfs_agf		*agf = XFS_BUF_TO_AGF(bp);

	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		if (!uuid_equal(&agf->agf_uuid, &mp->m_sb.sb_meta_uuid))
			return __this_address;
		if (!xfs_log_check_lsn(mp,
				be64_to_cpu(XFS_BUF_TO_AGF(bp)->agf_lsn)))
			return __this_address;
	}

	if (!xfs_verify_magic(bp, agf->agf_magicnum))
		return __this_address;

	if (!(XFS_AGF_GOOD_VERSION(be32_to_cpu(agf->agf_versionnum)) &&
	      be32_to_cpu(agf->agf_freeblks) <= be32_to_cpu(agf->agf_length) &&
	      be32_to_cpu(agf->agf_flfirst) < xfs_agfl_size(mp) &&
	      be32_to_cpu(agf->agf_fllast) < xfs_agfl_size(mp) &&
	      be32_to_cpu(agf->agf_flcount) <= xfs_agfl_size(mp)))
		return __this_address;

	if (be32_to_cpu(agf->agf_levels[XFS_BTNUM_BNO]) < 1 ||
	    be32_to_cpu(agf->agf_levels[XFS_BTNUM_CNT]) < 1 ||
	    be32_to_cpu(agf->agf_levels[XFS_BTNUM_BNO]) > XFS_BTREE_MAXLEVELS ||
	    be32_to_cpu(agf->agf_levels[XFS_BTNUM_CNT]) > XFS_BTREE_MAXLEVELS)
		return __this_address;

	if (xfs_sb_version_hasrmapbt(&mp->m_sb) &&
	    (be32_to_cpu(agf->agf_levels[XFS_BTNUM_RMAP]) < 1 ||
	     be32_to_cpu(agf->agf_levels[XFS_BTNUM_RMAP]) > XFS_BTREE_MAXLEVELS))
		return __this_address;

	/*
	 * during growfs operations, the perag is not fully initialised,
	 * so we can't use it for any useful checking. growfs ensures we can't
	 * use it by using uncached buffers that don't have the perag attached
	 * so we can detect and avoid this problem.
	 */
	if (bp->b_pag && be32_to_cpu(agf->agf_seqno) != bp->b_pag->pag_agno)
		return __this_address;

	if (xfs_sb_version_haslazysbcount(&mp->m_sb) &&
	    be32_to_cpu(agf->agf_btreeblks) > be32_to_cpu(agf->agf_length))
		return __this_address;

	if (xfs_sb_version_hasreflink(&mp->m_sb) &&
	    (be32_to_cpu(agf->agf_refcount_level) < 1 ||
	     be32_to_cpu(agf->agf_refcount_level) > XFS_BTREE_MAXLEVELS))
		return __this_address;

	return NULL;

}