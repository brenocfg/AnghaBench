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
struct inode {int dummy; } ;
struct coda_inode_info {int c_cached_perm; int /*<<< orphan*/  c_lock; int /*<<< orphan*/  c_uid; int /*<<< orphan*/  c_cached_epoch; } ;

/* Variables and functions */
 struct coda_inode_info* ITOC (struct inode*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  permission_epoch ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void coda_cache_enter(struct inode *inode, int mask)
{
	struct coda_inode_info *cii = ITOC(inode);

	spin_lock(&cii->c_lock);
	cii->c_cached_epoch = atomic_read(&permission_epoch);
	if (!uid_eq(cii->c_uid, current_fsuid())) {
		cii->c_uid = current_fsuid();
                cii->c_cached_perm = mask;
        } else
                cii->c_cached_perm |= mask;
	spin_unlock(&cii->c_lock);
}