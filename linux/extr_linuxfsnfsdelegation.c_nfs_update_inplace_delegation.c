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
struct TYPE_3__ {int /*<<< orphan*/  seqid; } ;
struct nfs_delegation {int /*<<< orphan*/  type; TYPE_1__ stateid; } ;

/* Variables and functions */
 scalar_t__ nfs4_stateid_is_newer (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void
nfs_update_inplace_delegation(struct nfs_delegation *delegation,
		const struct nfs_delegation *update)
{
	if (nfs4_stateid_is_newer(&update->stateid, &delegation->stateid)) {
		delegation->stateid.seqid = update->stateid.seqid;
		smp_wmb();
		delegation->type = update->type;
	}
}