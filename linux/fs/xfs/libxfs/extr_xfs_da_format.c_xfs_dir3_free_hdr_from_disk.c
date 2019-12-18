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
struct xfs_dir3_icfree_hdr {void* magic; void* nused; void* nvalid; void* firstdb; } ;
struct TYPE_2__ {int /*<<< orphan*/  magic; } ;
struct xfs_dir3_free_hdr {int /*<<< orphan*/  nused; int /*<<< orphan*/  nvalid; int /*<<< orphan*/  firstdb; TYPE_1__ hdr; } ;
struct xfs_dir2_free {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* XFS_DIR3_FREE_MAGIC ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_dir3_free_hdr_from_disk(
	struct xfs_dir3_icfree_hdr	*to,
	struct xfs_dir2_free		*from)
{
	struct xfs_dir3_free_hdr *hdr3 = (struct xfs_dir3_free_hdr *)from;

	to->magic = be32_to_cpu(hdr3->hdr.magic);
	to->firstdb = be32_to_cpu(hdr3->firstdb);
	to->nvalid = be32_to_cpu(hdr3->nvalid);
	to->nused = be32_to_cpu(hdr3->nused);

	ASSERT(to->magic == XFS_DIR3_FREE_MAGIC);
}