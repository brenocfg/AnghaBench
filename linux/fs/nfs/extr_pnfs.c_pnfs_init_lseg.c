#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pnfs_layout_range {int dummy; } ;
struct pnfs_layout_segment {int /*<<< orphan*/  pls_seq; struct pnfs_layout_range pls_range; struct pnfs_layout_hdr* pls_layout; int /*<<< orphan*/  pls_flags; int /*<<< orphan*/  pls_refcount; int /*<<< orphan*/  pls_lc_list; int /*<<< orphan*/  pls_list; } ;
struct pnfs_layout_hdr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  seqid; } ;
typedef  TYPE_1__ nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS_LSEG_VALID ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pnfs_init_lseg(struct pnfs_layout_hdr *lo, struct pnfs_layout_segment *lseg,
		const struct pnfs_layout_range *range,
		const nfs4_stateid *stateid)
{
	INIT_LIST_HEAD(&lseg->pls_list);
	INIT_LIST_HEAD(&lseg->pls_lc_list);
	refcount_set(&lseg->pls_refcount, 1);
	set_bit(NFS_LSEG_VALID, &lseg->pls_flags);
	lseg->pls_layout = lo;
	lseg->pls_range = *range;
	lseg->pls_seq = be32_to_cpu(stateid->seqid);
}