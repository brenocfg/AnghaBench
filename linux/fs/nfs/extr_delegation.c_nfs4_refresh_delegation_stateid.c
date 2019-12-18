#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  seqid; } ;
struct nfs_delegation {TYPE_3__ stateid; } ;
struct inode {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  seqid; } ;
typedef  TYPE_1__ nfs4_stateid ;
struct TYPE_8__ {int /*<<< orphan*/  delegation; } ;

/* Variables and functions */
 TYPE_5__* NFS_I (struct inode*) ; 
 scalar_t__ nfs4_stateid_match_other (TYPE_1__*,TYPE_3__*) ; 
 struct nfs_delegation* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

bool nfs4_refresh_delegation_stateid(nfs4_stateid *dst, struct inode *inode)
{
	struct nfs_delegation *delegation;
	bool ret = false;
	if (!inode)
		goto out;

	rcu_read_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);
	if (delegation != NULL &&
	    nfs4_stateid_match_other(dst, &delegation->stateid)) {
		dst->seqid = delegation->stateid.seqid;
		ret = true;
	}
	rcu_read_unlock();
out:
	return ret;
}