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
struct TYPE_2__ {int /*<<< orphan*/  sb_meta_uuid; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct xfs_buf {int dummy; } ;
struct xfs_agfl {int /*<<< orphan*/  agfl_uuid; void* agfl_seqno; void* agfl_magicnum; } ;
struct aghdr_init_data {int /*<<< orphan*/  agno; } ;
typedef  void* __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NULLAGBLOCK ; 
 int /*<<< orphan*/  XFS_AGFL_MAGIC ; 
 struct xfs_agfl* XFS_BUF_TO_AGFL (struct xfs_buf*) ; 
 void** XFS_BUF_TO_AGFL_BNO (struct xfs_mount*,struct xfs_buf*) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int xfs_agfl_size (struct xfs_mount*) ; 
 scalar_t__ xfs_sb_version_hascrc (TYPE_1__*) ; 

__attribute__((used)) static void
xfs_agflblock_init(
	struct xfs_mount	*mp,
	struct xfs_buf		*bp,
	struct aghdr_init_data	*id)
{
	struct xfs_agfl		*agfl = XFS_BUF_TO_AGFL(bp);
	__be32			*agfl_bno;
	int			bucket;

	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		agfl->agfl_magicnum = cpu_to_be32(XFS_AGFL_MAGIC);
		agfl->agfl_seqno = cpu_to_be32(id->agno);
		uuid_copy(&agfl->agfl_uuid, &mp->m_sb.sb_meta_uuid);
	}

	agfl_bno = XFS_BUF_TO_AGFL_BNO(mp, bp);
	for (bucket = 0; bucket < xfs_agfl_size(mp); bucket++)
		agfl_bno[bucket] = cpu_to_be32(NULLAGBLOCK);
}