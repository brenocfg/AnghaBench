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
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ d_ancestor (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  rename_lock ; 

bool is_subdir(struct dentry *new_dentry, struct dentry *old_dentry)
{
	bool result;
	unsigned seq;

	if (new_dentry == old_dentry)
		return true;

	do {
		/* for restarting inner loop in case of seq retry */
		seq = read_seqbegin(&rename_lock);
		/*
		 * Need rcu_readlock to protect against the d_parent trashing
		 * due to d_move
		 */
		rcu_read_lock();
		if (d_ancestor(old_dentry, new_dentry))
			result = true;
		else
			result = false;
		rcu_read_unlock();
	} while (read_seqretry(&rename_lock, seq));

	return result;
}