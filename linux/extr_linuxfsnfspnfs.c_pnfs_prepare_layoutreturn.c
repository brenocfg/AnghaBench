#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pnfs_layout_hdr {scalar_t__ plh_return_seq; int plh_return_iomode; int /*<<< orphan*/  plh_stateid; int /*<<< orphan*/  plh_flags; int /*<<< orphan*/  plh_outstanding; } ;
struct TYPE_4__ {int /*<<< orphan*/  seqid; } ;
typedef  TYPE_1__ nfs4_stateid ;
typedef  enum pnfs_iomode { ____Placeholder_pnfs_iomode } pnfs_iomode ;

/* Variables and functions */
 int IOMODE_ANY ; 
 int /*<<< orphan*/  NFS_LAYOUT_RETURN ; 
 int /*<<< orphan*/  NFS_LAYOUT_RETURN_LOCK ; 
 int /*<<< orphan*/  NFS_LAYOUT_RETURN_REQUESTED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnfs_clear_layoutreturn_info (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  pnfs_get_layout_hdr (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
pnfs_prepare_layoutreturn(struct pnfs_layout_hdr *lo,
		nfs4_stateid *stateid,
		enum pnfs_iomode *iomode)
{
	/* Serialise LAYOUTGET/LAYOUTRETURN */
	if (atomic_read(&lo->plh_outstanding) != 0)
		return false;
	if (test_and_set_bit(NFS_LAYOUT_RETURN_LOCK, &lo->plh_flags))
		return false;
	set_bit(NFS_LAYOUT_RETURN, &lo->plh_flags);
	pnfs_get_layout_hdr(lo);
	if (test_bit(NFS_LAYOUT_RETURN_REQUESTED, &lo->plh_flags)) {
		if (stateid != NULL) {
			nfs4_stateid_copy(stateid, &lo->plh_stateid);
			if (lo->plh_return_seq != 0)
				stateid->seqid = cpu_to_be32(lo->plh_return_seq);
		}
		if (iomode != NULL)
			*iomode = lo->plh_return_iomode;
		pnfs_clear_layoutreturn_info(lo);
		return true;
	}
	if (stateid != NULL)
		nfs4_stateid_copy(stateid, &lo->plh_stateid);
	if (iomode != NULL)
		*iomode = IOMODE_ANY;
	return true;
}