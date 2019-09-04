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
struct TYPE_3__ {void* magic; void* back; void* forw; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
struct xfs_dir3_leaf_hdr {void* stale; void* count; TYPE_2__ info; } ;
struct xfs_dir3_icleaf_hdr {scalar_t__ magic; scalar_t__ count; scalar_t__ stale; int /*<<< orphan*/  back; int /*<<< orphan*/  forw; } ;
struct xfs_dir2_leaf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR3_LEAF1_MAGIC ; 
 scalar_t__ XFS_DIR3_LEAFN_MAGIC ; 
 void* cpu_to_be16 (scalar_t__) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_dir3_leaf_hdr_to_disk(
	struct xfs_dir2_leaf		*to,
	struct xfs_dir3_icleaf_hdr	*from)
{
	struct xfs_dir3_leaf_hdr *hdr3 = (struct xfs_dir3_leaf_hdr *)to;

	ASSERT(from->magic == XFS_DIR3_LEAF1_MAGIC ||
	       from->magic == XFS_DIR3_LEAFN_MAGIC);

	hdr3->info.hdr.forw = cpu_to_be32(from->forw);
	hdr3->info.hdr.back = cpu_to_be32(from->back);
	hdr3->info.hdr.magic = cpu_to_be16(from->magic);
	hdr3->count = cpu_to_be16(from->count);
	hdr3->stale = cpu_to_be16(from->stale);
}