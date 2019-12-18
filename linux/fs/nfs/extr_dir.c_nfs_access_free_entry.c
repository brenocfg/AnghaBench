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
struct nfs_access_entry {int /*<<< orphan*/  cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct nfs_access_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_access_nr_entries ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_head ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static void nfs_access_free_entry(struct nfs_access_entry *entry)
{
	put_cred(entry->cred);
	kfree_rcu(entry, rcu_head);
	smp_mb__before_atomic();
	atomic_long_dec(&nfs_access_nr_entries);
	smp_mb__after_atomic();
}