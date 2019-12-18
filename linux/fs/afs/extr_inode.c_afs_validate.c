#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct key {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {int /*<<< orphan*/  validate_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  vfs_inode; TYPE_1__ fid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VNODE_CB_PROMISED ; 
 int /*<<< orphan*/  AFS_VNODE_DELETED ; 
 int /*<<< orphan*/  AFS_VNODE_ZAP_DATA ; 
 int ENOENT ; 
 int ESTALE ; 
 int /*<<< orphan*/  _debug (char*,...) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int afs_check_validity (struct afs_vnode*) ; 
 int afs_fetch_status (struct afs_vnode*,struct key*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  afs_zap_data (struct afs_vnode*) ; 
 int /*<<< orphan*/  clear_nlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int afs_validate(struct afs_vnode *vnode, struct key *key)
{
	bool valid;
	int ret;

	_enter("{v={%llx:%llu} fl=%lx},%x",
	       vnode->fid.vid, vnode->fid.vnode, vnode->flags,
	       key_serial(key));

	rcu_read_lock();
	valid = afs_check_validity(vnode);
	rcu_read_unlock();

	if (test_bit(AFS_VNODE_DELETED, &vnode->flags))
		clear_nlink(&vnode->vfs_inode);

	if (valid)
		goto valid;

	down_write(&vnode->validate_lock);

	/* if the promise has expired, we need to check the server again to get
	 * a new promise - note that if the (parent) directory's metadata was
	 * changed then the security may be different and we may no longer have
	 * access */
	if (!test_bit(AFS_VNODE_CB_PROMISED, &vnode->flags)) {
		_debug("not promised");
		ret = afs_fetch_status(vnode, key, false, NULL);
		if (ret < 0) {
			if (ret == -ENOENT) {
				set_bit(AFS_VNODE_DELETED, &vnode->flags);
				ret = -ESTALE;
			}
			goto error_unlock;
		}
		_debug("new promise [fl=%lx]", vnode->flags);
	}

	if (test_bit(AFS_VNODE_DELETED, &vnode->flags)) {
		_debug("file already deleted");
		ret = -ESTALE;
		goto error_unlock;
	}

	/* if the vnode's data version number changed then its contents are
	 * different */
	if (test_and_clear_bit(AFS_VNODE_ZAP_DATA, &vnode->flags))
		afs_zap_data(vnode);
	up_write(&vnode->validate_lock);
valid:
	_leave(" = 0");
	return 0;

error_unlock:
	up_write(&vnode->validate_lock);
	_leave(" = %d", ret);
	return ret;
}