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
typedef  int xfs_extlen_t ;
struct TYPE_4__ {int sb_logblocks; int /*<<< orphan*/  sb_logstart; int /*<<< orphan*/  sb_meta_uuid; } ;
struct xfs_mount {int m_ag_prealloc_blocks; TYPE_1__ m_sb; } ;
struct xfs_buf {int dummy; } ;
struct xfs_agf {void* agf_longest; void* agf_freeblks; void* agf_refcount_blocks; void* agf_refcount_level; void* agf_refcount_root; int /*<<< orphan*/  agf_uuid; scalar_t__ agf_flcount; scalar_t__ agf_fllast; void* agf_flfirst; void* agf_rmap_blocks; void** agf_levels; void** agf_roots; void* agf_length; void* agf_seqno; void* agf_versionnum; void* agf_magicnum; } ;
struct aghdr_init_data {int agno; int agsize; } ;
typedef  int int64_t ;

/* Variables and functions */
 int XFS_AGF_MAGIC ; 
 int XFS_AGF_VERSION ; 
 int XFS_BNO_BLOCK (struct xfs_mount*) ; 
 size_t XFS_BTNUM_BNOi ; 
 size_t XFS_BTNUM_CNTi ; 
 size_t XFS_BTNUM_RMAPi ; 
 struct xfs_agf* XFS_BUF_TO_AGF (struct xfs_buf*) ; 
 int XFS_CNT_BLOCK (struct xfs_mount*) ; 
 int XFS_FSB_TO_AGBNO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int XFS_RMAP_BLOCK (struct xfs_mount*) ; 
 int /*<<< orphan*/  be32_add_cpu (void**,int) ; 
 void* cpu_to_be32 (int) ; 
 scalar_t__ is_log_ag (struct xfs_mount*,struct aghdr_init_data*) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int xfs_refc_block (struct xfs_mount*) ; 
 scalar_t__ xfs_sb_version_hascrc (TYPE_1__*) ; 
 scalar_t__ xfs_sb_version_hasreflink (TYPE_1__*) ; 
 scalar_t__ xfs_sb_version_hasrmapbt (TYPE_1__*) ; 

__attribute__((used)) static void
xfs_agfblock_init(
	struct xfs_mount	*mp,
	struct xfs_buf		*bp,
	struct aghdr_init_data	*id)
{
	struct xfs_agf		*agf = XFS_BUF_TO_AGF(bp);
	xfs_extlen_t		tmpsize;

	agf->agf_magicnum = cpu_to_be32(XFS_AGF_MAGIC);
	agf->agf_versionnum = cpu_to_be32(XFS_AGF_VERSION);
	agf->agf_seqno = cpu_to_be32(id->agno);
	agf->agf_length = cpu_to_be32(id->agsize);
	agf->agf_roots[XFS_BTNUM_BNOi] = cpu_to_be32(XFS_BNO_BLOCK(mp));
	agf->agf_roots[XFS_BTNUM_CNTi] = cpu_to_be32(XFS_CNT_BLOCK(mp));
	agf->agf_levels[XFS_BTNUM_BNOi] = cpu_to_be32(1);
	agf->agf_levels[XFS_BTNUM_CNTi] = cpu_to_be32(1);
	if (xfs_sb_version_hasrmapbt(&mp->m_sb)) {
		agf->agf_roots[XFS_BTNUM_RMAPi] =
					cpu_to_be32(XFS_RMAP_BLOCK(mp));
		agf->agf_levels[XFS_BTNUM_RMAPi] = cpu_to_be32(1);
		agf->agf_rmap_blocks = cpu_to_be32(1);
	}

	agf->agf_flfirst = cpu_to_be32(1);
	agf->agf_fllast = 0;
	agf->agf_flcount = 0;
	tmpsize = id->agsize - mp->m_ag_prealloc_blocks;
	agf->agf_freeblks = cpu_to_be32(tmpsize);
	agf->agf_longest = cpu_to_be32(tmpsize);
	if (xfs_sb_version_hascrc(&mp->m_sb))
		uuid_copy(&agf->agf_uuid, &mp->m_sb.sb_meta_uuid);
	if (xfs_sb_version_hasreflink(&mp->m_sb)) {
		agf->agf_refcount_root = cpu_to_be32(
				xfs_refc_block(mp));
		agf->agf_refcount_level = cpu_to_be32(1);
		agf->agf_refcount_blocks = cpu_to_be32(1);
	}

	if (is_log_ag(mp, id)) {
		int64_t	logblocks = mp->m_sb.sb_logblocks;

		be32_add_cpu(&agf->agf_freeblks, -logblocks);
		agf->agf_longest = cpu_to_be32(id->agsize -
			XFS_FSB_TO_AGBNO(mp, mp->m_sb.sb_logstart) - logblocks);
	}
}