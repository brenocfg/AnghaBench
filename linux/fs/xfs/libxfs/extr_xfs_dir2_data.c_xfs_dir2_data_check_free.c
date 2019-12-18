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
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
typedef  int xfs_dir2_data_aoff_t ;
struct xfs_dir2_data_unused {int /*<<< orphan*/  length; int /*<<< orphan*/  freetag; } ;
struct xfs_dir2_data_hdr {scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DIR2_BLOCK_MAGIC ; 
 int XFS_DIR2_DATA_FREE_TAG ; 
 int /*<<< orphan*/  XFS_DIR2_DATA_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_BLOCK_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_DATA_MAGIC ; 
 int /*<<< orphan*/ * __this_address ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xfs_dir2_data_unused_tag_p (struct xfs_dir2_data_unused*) ; 

__attribute__((used)) static inline xfs_failaddr_t
xfs_dir2_data_check_free(
	struct xfs_dir2_data_hdr	*hdr,
	struct xfs_dir2_data_unused	*dup,
	xfs_dir2_data_aoff_t		offset,
	xfs_dir2_data_aoff_t		len)
{
	if (hdr->magic != cpu_to_be32(XFS_DIR2_DATA_MAGIC) &&
	    hdr->magic != cpu_to_be32(XFS_DIR3_DATA_MAGIC) &&
	    hdr->magic != cpu_to_be32(XFS_DIR2_BLOCK_MAGIC) &&
	    hdr->magic != cpu_to_be32(XFS_DIR3_BLOCK_MAGIC))
		return __this_address;
	if (be16_to_cpu(dup->freetag) != XFS_DIR2_DATA_FREE_TAG)
		return __this_address;
	if (offset < (char *)dup - (char *)hdr)
		return __this_address;
	if (offset + len > (char *)dup + be16_to_cpu(dup->length) - (char *)hdr)
		return __this_address;
	if ((char *)dup - (char *)hdr !=
			be16_to_cpu(*xfs_dir2_data_unused_tag_p(dup)))
		return __this_address;
	return NULL;
}