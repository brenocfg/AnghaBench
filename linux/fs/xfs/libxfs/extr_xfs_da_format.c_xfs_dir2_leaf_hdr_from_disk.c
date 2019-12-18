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
struct xfs_dir3_icleaf_hdr {scalar_t__ magic; void* stale; void* count; void* back; void* forw; } ;
struct TYPE_4__ {int /*<<< orphan*/  magic; int /*<<< orphan*/  back; int /*<<< orphan*/  forw; } ;
struct TYPE_3__ {int /*<<< orphan*/  stale; int /*<<< orphan*/  count; TYPE_2__ info; } ;
struct xfs_dir2_leaf {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR2_LEAF1_MAGIC ; 
 scalar_t__ XFS_DIR2_LEAFN_MAGIC ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_dir2_leaf_hdr_from_disk(
	struct xfs_dir3_icleaf_hdr	*to,
	struct xfs_dir2_leaf		*from)
{
	to->forw = be32_to_cpu(from->hdr.info.forw);
	to->back = be32_to_cpu(from->hdr.info.back);
	to->magic = be16_to_cpu(from->hdr.info.magic);
	to->count = be16_to_cpu(from->hdr.count);
	to->stale = be16_to_cpu(from->hdr.stale);

	ASSERT(to->magic == XFS_DIR2_LEAF1_MAGIC ||
	       to->magic == XFS_DIR2_LEAFN_MAGIC);
}