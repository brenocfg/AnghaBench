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
typedef  int /*<<< orphan*/  u32 ;
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_barrier; } ;
struct TYPE_3__ {int /*<<< orphan*/  seqid; } ;
typedef  TYPE_1__ nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_seqid_is_newer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
pnfs_layout_stateid_blocked(const struct pnfs_layout_hdr *lo,
		const nfs4_stateid *stateid)
{
	u32 seqid = be32_to_cpu(stateid->seqid);

	return !pnfs_seqid_is_newer(seqid, lo->plh_barrier);
}