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
struct path {int /*<<< orphan*/  dentry; } ;

/* Variables and functions */
 int __path_is_mountpoint (struct path const*) ; 
 int /*<<< orphan*/  d_mountpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_lock ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 

bool path_is_mountpoint(const struct path *path)
{
	unsigned seq;
	bool res;

	if (!d_mountpoint(path->dentry))
		return false;

	rcu_read_lock();
	do {
		seq = read_seqbegin(&mount_lock);
		res = __path_is_mountpoint(path);
	} while (read_seqretry(&mount_lock, seq));
	rcu_read_unlock();

	return res;
}