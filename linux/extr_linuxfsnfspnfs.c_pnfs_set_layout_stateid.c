#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int /*<<< orphan*/  seqid; } ;
struct pnfs_layout_hdr {scalar_t__ plh_barrier; int /*<<< orphan*/  plh_outstanding; TYPE_3__ plh_stateid; int /*<<< orphan*/  plh_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  seqid; } ;
typedef  TYPE_1__ nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_LAYOUT_INVALID_STID ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (TYPE_3__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  pnfs_clear_layoutreturn_info (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  pnfs_layout_is_valid (struct pnfs_layout_hdr*) ; 
 scalar_t__ pnfs_seqid_is_newer (scalar_t__,scalar_t__) ; 

void
pnfs_set_layout_stateid(struct pnfs_layout_hdr *lo, const nfs4_stateid *new,
			bool update_barrier)
{
	u32 oldseq, newseq, new_barrier = 0;

	oldseq = be32_to_cpu(lo->plh_stateid.seqid);
	newseq = be32_to_cpu(new->seqid);

	if (!pnfs_layout_is_valid(lo)) {
		nfs4_stateid_copy(&lo->plh_stateid, new);
		lo->plh_barrier = newseq;
		pnfs_clear_layoutreturn_info(lo);
		clear_bit(NFS_LAYOUT_INVALID_STID, &lo->plh_flags);
		return;
	}
	if (pnfs_seqid_is_newer(newseq, oldseq)) {
		nfs4_stateid_copy(&lo->plh_stateid, new);
		/*
		 * Because of wraparound, we want to keep the barrier
		 * "close" to the current seqids.
		 */
		new_barrier = newseq - atomic_read(&lo->plh_outstanding);
	}
	if (update_barrier)
		new_barrier = be32_to_cpu(new->seqid);
	else if (new_barrier == 0)
		return;
	if (pnfs_seqid_is_newer(new_barrier, lo->plh_barrier))
		lo->plh_barrier = new_barrier;
}