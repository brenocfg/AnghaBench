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
typedef  scalar_t__ xfs_extlen_t ;
struct xfs_trans {int dummy; } ;
struct TYPE_2__ {int sb_agcount; scalar_t__ sb_agblocks; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct xfs_buf {int dummy; } ;
struct xfs_agi {scalar_t__ agi_length; } ;
struct xfs_agf {scalar_t__ agf_length; } ;
struct aghdr_init_data {int agno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_AGB_TO_FSB (struct xfs_mount*,int,scalar_t__) ; 
 int /*<<< orphan*/  XFS_AGF_LENGTH ; 
 int /*<<< orphan*/  XFS_AGI_LENGTH ; 
 int /*<<< orphan*/  XFS_AG_RESV_NONE ; 
 struct xfs_agf* XFS_BUF_TO_AGF (struct xfs_buf*) ; 
 struct xfs_agi* XFS_BUF_TO_AGI (struct xfs_buf*) ; 
 int /*<<< orphan*/  XFS_RMAP_OINFO_SKIP_UPDATE ; 
 int /*<<< orphan*/  be32_add_cpu (scalar_t__*,scalar_t__) ; 
 scalar_t__ be32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  xfs_alloc_log_agf (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int xfs_alloc_read_agf (struct xfs_mount*,struct xfs_trans*,int,int /*<<< orphan*/ ,struct xfs_buf**) ; 
 int xfs_free_extent (struct xfs_trans*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ialloc_log_agi (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int xfs_ialloc_read_agi (struct xfs_mount*,struct xfs_trans*,int,struct xfs_buf**) ; 
 int xfs_rmap_free (struct xfs_trans*,struct xfs_buf*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

int
xfs_ag_extend_space(
	struct xfs_mount	*mp,
	struct xfs_trans	*tp,
	struct aghdr_init_data	*id,
	xfs_extlen_t		len)
{
	struct xfs_buf		*bp;
	struct xfs_agi		*agi;
	struct xfs_agf		*agf;
	int			error;

	/*
	 * Change the agi length.
	 */
	error = xfs_ialloc_read_agi(mp, tp, id->agno, &bp);
	if (error)
		return error;

	agi = XFS_BUF_TO_AGI(bp);
	be32_add_cpu(&agi->agi_length, len);
	ASSERT(id->agno == mp->m_sb.sb_agcount - 1 ||
	       be32_to_cpu(agi->agi_length) == mp->m_sb.sb_agblocks);
	xfs_ialloc_log_agi(tp, bp, XFS_AGI_LENGTH);

	/*
	 * Change agf length.
	 */
	error = xfs_alloc_read_agf(mp, tp, id->agno, 0, &bp);
	if (error)
		return error;

	agf = XFS_BUF_TO_AGF(bp);
	be32_add_cpu(&agf->agf_length, len);
	ASSERT(agf->agf_length == agi->agi_length);
	xfs_alloc_log_agf(tp, bp, XFS_AGF_LENGTH);

	/*
	 * Free the new space.
	 *
	 * XFS_RMAP_OINFO_SKIP_UPDATE is used here to tell the rmap btree that
	 * this doesn't actually exist in the rmap btree.
	 */
	error = xfs_rmap_free(tp, bp, id->agno,
				be32_to_cpu(agf->agf_length) - len,
				len, &XFS_RMAP_OINFO_SKIP_UPDATE);
	if (error)
		return error;

	return  xfs_free_extent(tp, XFS_AGB_TO_FSB(mp, id->agno,
					be32_to_cpu(agf->agf_length) - len),
				len, &XFS_RMAP_OINFO_SKIP_UPDATE,
				XFS_AG_RESV_NONE);
}