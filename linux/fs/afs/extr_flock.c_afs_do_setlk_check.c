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
struct key {int dummy; } ;
struct afs_vnode {int dummy; } ;
typedef  enum afs_flock_mode { ____Placeholder_afs_flock_mode } afs_flock_mode ;
typedef  scalar_t__ afs_lock_type_t ;
typedef  int afs_access_t ;

/* Variables and functions */
 int AFS_ACE_INSERT ; 
 int AFS_ACE_LOCK ; 
 int AFS_ACE_WRITE ; 
 scalar_t__ AFS_LOCK_READ ; 
 int EACCES ; 
 int afs_check_permit (struct afs_vnode*,struct key*,int*) ; 
 int afs_validate (struct afs_vnode*,struct key*) ; 

__attribute__((used)) static int afs_do_setlk_check(struct afs_vnode *vnode, struct key *key,
			      enum afs_flock_mode mode, afs_lock_type_t type)
{
	afs_access_t access;
	int ret;

	/* Make sure we've got a callback on this file and that our view of the
	 * data version is up to date.
	 */
	ret = afs_validate(vnode, key);
	if (ret < 0)
		return ret;

	/* Check the permission set to see if we're actually going to be
	 * allowed to get a lock on this file.
	 */
	ret = afs_check_permit(vnode, key, &access);
	if (ret < 0)
		return ret;

	/* At a rough estimation, you need LOCK, WRITE or INSERT perm to
	 * read-lock a file and WRITE or INSERT perm to write-lock a file.
	 *
	 * We can't rely on the server to do this for us since if we want to
	 * share a read lock that we already have, we won't go the server.
	 */
	if (type == AFS_LOCK_READ) {
		if (!(access & (AFS_ACE_INSERT | AFS_ACE_WRITE | AFS_ACE_LOCK)))
			return -EACCES;
	} else {
		if (!(access & (AFS_ACE_INSERT | AFS_ACE_WRITE)))
			return -EACCES;
	}

	return 0;
}