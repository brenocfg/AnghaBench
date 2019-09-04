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
struct xfs_dir3_icfree_hdr {scalar_t__ magic; scalar_t__ firstdb; scalar_t__ nvalid; scalar_t__ nused; } ;
struct TYPE_2__ {void* nused; void* nvalid; void* firstdb; void* magic; } ;
struct xfs_dir2_free {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR2_FREE_MAGIC ; 
 void* cpu_to_be32 (scalar_t__) ; 

__attribute__((used)) static void
xfs_dir2_free_hdr_to_disk(
	struct xfs_dir2_free		*to,
	struct xfs_dir3_icfree_hdr	*from)
{
	ASSERT(from->magic == XFS_DIR2_FREE_MAGIC);

	to->hdr.magic = cpu_to_be32(from->magic);
	to->hdr.firstdb = cpu_to_be32(from->firstdb);
	to->hdr.nvalid = cpu_to_be32(from->nvalid);
	to->hdr.nused = cpu_to_be32(from->nused);
}