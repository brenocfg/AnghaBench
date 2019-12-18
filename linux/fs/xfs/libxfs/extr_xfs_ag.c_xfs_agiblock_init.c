#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sb_meta_uuid; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct xfs_buf {int dummy; } ;
struct xfs_agi {void** agi_unlinked; void* agi_free_level; void* agi_free_root; int /*<<< orphan*/  agi_uuid; void* agi_dirino; void* agi_newino; scalar_t__ agi_freecount; void* agi_level; void* agi_root; scalar_t__ agi_count; void* agi_length; void* agi_seqno; void* agi_versionnum; void* agi_magicnum; } ;
struct aghdr_init_data {int agno; int agsize; } ;

/* Variables and functions */
 int NULLAGINO ; 
 int XFS_AGI_MAGIC ; 
 int XFS_AGI_UNLINKED_BUCKETS ; 
 int XFS_AGI_VERSION ; 
 struct xfs_agi* XFS_BUF_TO_AGI (struct xfs_buf*) ; 
 int XFS_FIBT_BLOCK (struct xfs_mount*) ; 
 int XFS_IBT_BLOCK (struct xfs_mount*) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xfs_sb_version_hascrc (TYPE_1__*) ; 
 scalar_t__ xfs_sb_version_hasfinobt (TYPE_1__*) ; 

__attribute__((used)) static void
xfs_agiblock_init(
	struct xfs_mount	*mp,
	struct xfs_buf		*bp,
	struct aghdr_init_data	*id)
{
	struct xfs_agi		*agi = XFS_BUF_TO_AGI(bp);
	int			bucket;

	agi->agi_magicnum = cpu_to_be32(XFS_AGI_MAGIC);
	agi->agi_versionnum = cpu_to_be32(XFS_AGI_VERSION);
	agi->agi_seqno = cpu_to_be32(id->agno);
	agi->agi_length = cpu_to_be32(id->agsize);
	agi->agi_count = 0;
	agi->agi_root = cpu_to_be32(XFS_IBT_BLOCK(mp));
	agi->agi_level = cpu_to_be32(1);
	agi->agi_freecount = 0;
	agi->agi_newino = cpu_to_be32(NULLAGINO);
	agi->agi_dirino = cpu_to_be32(NULLAGINO);
	if (xfs_sb_version_hascrc(&mp->m_sb))
		uuid_copy(&agi->agi_uuid, &mp->m_sb.sb_meta_uuid);
	if (xfs_sb_version_hasfinobt(&mp->m_sb)) {
		agi->agi_free_root = cpu_to_be32(XFS_FIBT_BLOCK(mp));
		agi->agi_free_level = cpu_to_be32(1);
	}
	for (bucket = 0; bucket < XFS_AGI_UNLINKED_BUCKETS; bucket++)
		agi->agi_unlinked[bucket] = cpu_to_be32(NULLAGINO);
}