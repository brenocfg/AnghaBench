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
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __d_move (struct dentry*,struct dentry*,int) ; 
 int /*<<< orphan*/  rename_lock ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

void d_exchange(struct dentry *dentry1, struct dentry *dentry2)
{
	write_seqlock(&rename_lock);

	WARN_ON(!dentry1->d_inode);
	WARN_ON(!dentry2->d_inode);
	WARN_ON(IS_ROOT(dentry1));
	WARN_ON(IS_ROOT(dentry2));

	__d_move(dentry1, dentry2, true);

	write_sequnlock(&rename_lock);
}