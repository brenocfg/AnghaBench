#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfs_dir3_icleaf_hdr {scalar_t__ magic; scalar_t__ count; scalar_t__ stale; int /*<<< orphan*/  back; int /*<<< orphan*/  forw; } ;
struct TYPE_3__ {void* magic; void* back; void* forw; } ;
struct TYPE_4__ {void* stale; void* count; TYPE_1__ info; } ;
struct xfs_dir2_leaf {TYPE_2__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR2_LEAF1_MAGIC ; 
 scalar_t__ XFS_DIR2_LEAFN_MAGIC ; 
 void* cpu_to_be16 (scalar_t__) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_dir2_leaf_hdr_to_disk(
	struct xfs_dir2_leaf		*to,
	struct xfs_dir3_icleaf_hdr	*from)
{
	ASSERT(from->magic == XFS_DIR2_LEAF1_MAGIC ||
	       from->magic == XFS_DIR2_LEAFN_MAGIC);

	to->hdr.info.forw = cpu_to_be32(from->forw);
	to->hdr.info.back = cpu_to_be32(from->back);
	to->hdr.info.magic = cpu_to_be16(from->magic);
	to->hdr.count = cpu_to_be16(from->count);
	to->hdr.stale = cpu_to_be16(from->stale);
}