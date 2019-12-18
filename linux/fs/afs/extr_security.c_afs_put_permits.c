#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct afs_permits {int /*<<< orphan*/  rcu; int /*<<< orphan*/  hash_node; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_permits_lock ; 
 int /*<<< orphan*/  afs_permits_rcu ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void afs_put_permits(struct afs_permits *permits)
{
	if (permits && refcount_dec_and_test(&permits->usage)) {
		spin_lock(&afs_permits_lock);
		hash_del_rcu(&permits->hash_node);
		spin_unlock(&afs_permits_lock);
		call_rcu(&permits->rcu, afs_permits_rcu);
	}
}