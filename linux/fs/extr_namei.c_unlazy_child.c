#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* dentry; int /*<<< orphan*/ * mnt; } ;
struct nameidata {int flags; TYPE_2__ path; int /*<<< orphan*/  m_seq; } ;
struct dentry {int /*<<< orphan*/  d_seq; int /*<<< orphan*/  d_lockref; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_lockref; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ECHILD ; 
 int LOOKUP_RCU ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  legitimize_links (struct nameidata*) ; 
 int /*<<< orphan*/  legitimize_mnt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  legitimize_root (struct nameidata*) ; 
 int /*<<< orphan*/  lockref_get_not_dead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int unlazy_child(struct nameidata *nd, struct dentry *dentry, unsigned seq)
{
	BUG_ON(!(nd->flags & LOOKUP_RCU));

	nd->flags &= ~LOOKUP_RCU;
	if (unlikely(!legitimize_links(nd)))
		goto out2;
	if (unlikely(!legitimize_mnt(nd->path.mnt, nd->m_seq)))
		goto out2;
	if (unlikely(!lockref_get_not_dead(&nd->path.dentry->d_lockref)))
		goto out1;

	/*
	 * We need to move both the parent and the dentry from the RCU domain
	 * to be properly refcounted. And the sequence number in the dentry
	 * validates *both* dentry counters, since we checked the sequence
	 * number of the parent after we got the child sequence number. So we
	 * know the parent must still be valid if the child sequence number is
	 */
	if (unlikely(!lockref_get_not_dead(&dentry->d_lockref)))
		goto out;
	if (unlikely(read_seqcount_retry(&dentry->d_seq, seq)))
		goto out_dput;
	/*
	 * Sequence counts matched. Now make sure that the root is
	 * still valid and get it if required.
	 */
	if (unlikely(!legitimize_root(nd)))
		goto out_dput;
	rcu_read_unlock();
	return 0;

out2:
	nd->path.mnt = NULL;
out1:
	nd->path.dentry = NULL;
out:
	rcu_read_unlock();
	return -ECHILD;
out_dput:
	rcu_read_unlock();
	dput(dentry);
	return -ECHILD;
}