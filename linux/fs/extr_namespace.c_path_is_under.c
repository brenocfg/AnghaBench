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
struct path {int /*<<< orphan*/  dentry; int /*<<< orphan*/  mnt; } ;

/* Variables and functions */
 int is_path_reachable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct path const*) ; 
 int /*<<< orphan*/  mount_lock ; 
 int /*<<< orphan*/  read_seqlock_excl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_sequnlock_excl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  real_mount (int /*<<< orphan*/ ) ; 

bool path_is_under(const struct path *path1, const struct path *path2)
{
	bool res;
	read_seqlock_excl(&mount_lock);
	res = is_path_reachable(real_mount(path1->mnt), path1->dentry, path2);
	read_sequnlock_excl(&mount_lock);
	return res;
}