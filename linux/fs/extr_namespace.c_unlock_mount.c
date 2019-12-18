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
struct mountpoint {struct dentry* m_dentry; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_lock ; 
 int /*<<< orphan*/  namespace_unlock () ; 
 int /*<<< orphan*/  put_mountpoint (struct mountpoint*) ; 
 int /*<<< orphan*/  read_seqlock_excl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_sequnlock_excl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unlock_mount(struct mountpoint *where)
{
	struct dentry *dentry = where->m_dentry;

	read_seqlock_excl(&mount_lock);
	put_mountpoint(where);
	read_sequnlock_excl(&mount_lock);

	namespace_unlock();
	inode_unlock(dentry->d_inode);
}