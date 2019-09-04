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
struct TYPE_2__ {int /*<<< orphan*/  rc_refcount; int /*<<< orphan*/  rc_blockcount; int /*<<< orphan*/  rc_startblock; } ;
union xfs_btree_rec {TYPE_1__ refc; } ;
struct xfs_refcount_irec {void* rc_refcount; void* rc_blockcount; void* rc_startblock; } ;

/* Variables and functions */
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 

void
xfs_refcount_btrec_to_irec(
	union xfs_btree_rec		*rec,
	struct xfs_refcount_irec	*irec)
{
	irec->rc_startblock = be32_to_cpu(rec->refc.rc_startblock);
	irec->rc_blockcount = be32_to_cpu(rec->refc.rc_blockcount);
	irec->rc_refcount = be32_to_cpu(rec->refc.rc_refcount);
}