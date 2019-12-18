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
struct xfs_da_blkinfo {int /*<<< orphan*/  magic; } ;
struct xfs_da3_blkinfo {int /*<<< orphan*/  lsn; int /*<<< orphan*/  blkno; int /*<<< orphan*/  uuid; struct xfs_da_blkinfo hdr; } ;
struct xfs_buf {scalar_t__ b_bn; struct xfs_mount* b_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/ * __this_address ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_log_check_lsn (struct xfs_mount*,scalar_t__) ; 
 scalar_t__ xfs_sb_version_hascrc (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_verify_magic16 (struct xfs_buf*,int /*<<< orphan*/ ) ; 

xfs_failaddr_t
xfs_da3_blkinfo_verify(
	struct xfs_buf		*bp,
	struct xfs_da3_blkinfo	*hdr3)
{
	struct xfs_mount	*mp = bp->b_mount;
	struct xfs_da_blkinfo	*hdr = &hdr3->hdr;

	if (!xfs_verify_magic16(bp, hdr->magic))
		return __this_address;

	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		if (!uuid_equal(&hdr3->uuid, &mp->m_sb.sb_meta_uuid))
			return __this_address;
		if (be64_to_cpu(hdr3->blkno) != bp->b_bn)
			return __this_address;
		if (!xfs_log_check_lsn(mp, be64_to_cpu(hdr3->lsn)))
			return __this_address;
	}

	return NULL;
}