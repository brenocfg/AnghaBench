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
struct coda_inode_info {int c_cached_perm; scalar_t__ c_cached_epoch; int /*<<< orphan*/  c_lock; int /*<<< orphan*/  c_uid; } ;

/* Variables and functions */
 struct coda_inode_info* ITOC (struct inode*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  permission_epoch ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int coda_cache_check(struct inode *inode, int mask)
{
	struct coda_inode_info *cii = ITOC(inode);
	int hit;
	
	spin_lock(&cii->c_lock);
	hit = (mask & cii->c_cached_perm) == mask &&
	    uid_eq(cii->c_uid, current_fsuid()) &&
	    cii->c_cached_epoch == atomic_read(&permission_epoch);
	spin_unlock(&cii->c_lock);

	return hit;
}