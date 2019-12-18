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
struct TYPE_2__ {int /*<<< orphan*/  sb_meta_uuid; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct xfs_dsymlink_hdr {scalar_t__ sl_owner; int /*<<< orphan*/  sl_lsn; int /*<<< orphan*/  sl_bytes; int /*<<< orphan*/  sl_offset; int /*<<< orphan*/  sl_blkno; int /*<<< orphan*/  sl_uuid; int /*<<< orphan*/  sl_magic; } ;
struct xfs_buf {scalar_t__ b_bn; struct xfs_dsymlink_hdr* b_addr; struct xfs_mount* b_mount; } ;

/* Variables and functions */
 scalar_t__ XFS_SYMLINK_MAXLEN ; 
 int /*<<< orphan*/ * __this_address ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_log_check_lsn (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_sb_version_hascrc (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_verify_magic (struct xfs_buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static xfs_failaddr_t
xfs_symlink_verify(
	struct xfs_buf		*bp)
{
	struct xfs_mount	*mp = bp->b_mount;
	struct xfs_dsymlink_hdr	*dsl = bp->b_addr;

	if (!xfs_sb_version_hascrc(&mp->m_sb))
		return __this_address;
	if (!xfs_verify_magic(bp, dsl->sl_magic))
		return __this_address;
	if (!uuid_equal(&dsl->sl_uuid, &mp->m_sb.sb_meta_uuid))
		return __this_address;
	if (bp->b_bn != be64_to_cpu(dsl->sl_blkno))
		return __this_address;
	if (be32_to_cpu(dsl->sl_offset) +
				be32_to_cpu(dsl->sl_bytes) >= XFS_SYMLINK_MAXLEN)
		return __this_address;
	if (dsl->sl_owner == 0)
		return __this_address;
	if (!xfs_log_check_lsn(mp, be64_to_cpu(dsl->sl_lsn)))
		return __this_address;

	return NULL;
}