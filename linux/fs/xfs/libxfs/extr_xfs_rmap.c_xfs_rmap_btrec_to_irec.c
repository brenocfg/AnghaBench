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
struct TYPE_2__ {int /*<<< orphan*/  rm_offset; int /*<<< orphan*/  rm_owner; int /*<<< orphan*/  rm_blockcount; int /*<<< orphan*/  rm_startblock; } ;
union xfs_btree_rec {TYPE_1__ rmap; } ;
struct xfs_rmap_irec {int /*<<< orphan*/  rm_owner; void* rm_blockcount; void* rm_startblock; } ;

/* Variables and functions */
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int xfs_rmap_irec_offset_unpack (int /*<<< orphan*/ ,struct xfs_rmap_irec*) ; 

int
xfs_rmap_btrec_to_irec(
	union xfs_btree_rec	*rec,
	struct xfs_rmap_irec	*irec)
{
	irec->rm_startblock = be32_to_cpu(rec->rmap.rm_startblock);
	irec->rm_blockcount = be32_to_cpu(rec->rmap.rm_blockcount);
	irec->rm_owner = be64_to_cpu(rec->rmap.rm_owner);
	return xfs_rmap_irec_offset_unpack(be64_to_cpu(rec->rmap.rm_offset),
			irec);
}