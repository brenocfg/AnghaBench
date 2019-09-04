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
typedef  scalar_t__ xfs_daddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  sb_meta_uuid; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct xfs_attr3_rmt_hdr {scalar_t__ rm_magic; scalar_t__ rm_owner; int /*<<< orphan*/  rm_bytes; int /*<<< orphan*/  rm_offset; int /*<<< orphan*/  rm_blkno; int /*<<< orphan*/  rm_uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_ATTR3_RMT_MAGIC ; 
 int XFS_XATTR_SIZE_MAX ; 
 int /*<<< orphan*/ * __this_address ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_sb_version_hascrc (TYPE_1__*) ; 

__attribute__((used)) static xfs_failaddr_t
xfs_attr3_rmt_verify(
	struct xfs_mount	*mp,
	void			*ptr,
	int			fsbsize,
	xfs_daddr_t		bno)
{
	struct xfs_attr3_rmt_hdr *rmt = ptr;

	if (!xfs_sb_version_hascrc(&mp->m_sb))
		return __this_address;
	if (rmt->rm_magic != cpu_to_be32(XFS_ATTR3_RMT_MAGIC))
		return __this_address;
	if (!uuid_equal(&rmt->rm_uuid, &mp->m_sb.sb_meta_uuid))
		return __this_address;
	if (be64_to_cpu(rmt->rm_blkno) != bno)
		return __this_address;
	if (be32_to_cpu(rmt->rm_bytes) > fsbsize - sizeof(*rmt))
		return __this_address;
	if (be32_to_cpu(rmt->rm_offset) +
				be32_to_cpu(rmt->rm_bytes) > XFS_XATTR_SIZE_MAX)
		return __this_address;
	if (rmt->rm_owner == 0)
		return __this_address;

	return NULL;
}