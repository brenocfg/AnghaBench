#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int time64_t ;
struct key {int dummy; } ;
struct TYPE_9__ {scalar_t__ type; } ;
struct TYPE_6__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {scalar_t__ cb_s_break; scalar_t__ cb_v_break; int cb_expires_at; int /*<<< orphan*/  validate_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  vfs_inode; int /*<<< orphan*/  cb_lock; TYPE_5__* volume; TYPE_4__ status; TYPE_3__* cb_interest; TYPE_1__ fid; } ;
struct TYPE_10__ {scalar_t__ cb_v_break; } ;
struct TYPE_8__ {TYPE_2__* server; } ;
struct TYPE_7__ {scalar_t__ cb_s_break; } ;

/* Variables and functions */
 scalar_t__ AFS_FTYPE_DIR ; 
 int /*<<< orphan*/  AFS_VNODE_CB_PROMISED ; 
 int /*<<< orphan*/  AFS_VNODE_DELETED ; 
 int /*<<< orphan*/  AFS_VNODE_DIR_VALID ; 
 int /*<<< orphan*/  AFS_VNODE_ZAP_DATA ; 
 int ENOENT ; 
 int ESTALE ; 
 int /*<<< orphan*/  _debug (char*,...) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int afs_fetch_status (struct afs_vnode*,struct key*,int) ; 
 int /*<<< orphan*/  afs_zap_data (struct afs_vnode*) ; 
 int /*<<< orphan*/  clear_nlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int ktime_get_real_seconds () ; 
 int /*<<< orphan*/  read_seqlock_excl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_sequnlock_excl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int afs_validate(struct afs_vnode *vnode, struct key *key)
{
	time64_t now = ktime_get_real_seconds();
	bool valid;
	int ret;

	_enter("{v={%x:%u} fl=%lx},%x",
	       vnode->fid.vid, vnode->fid.vnode, vnode->flags,
	       key_serial(key));

	/* Quickly check the callback state.  Ideally, we'd use read_seqbegin
	 * here, but we have no way to pass the net namespace to the RCU
	 * cleanup for the server record.
	 */
	read_seqlock_excl(&vnode->cb_lock);

	if (test_bit(AFS_VNODE_CB_PROMISED, &vnode->flags)) {
		if (vnode->cb_s_break != vnode->cb_interest->server->cb_s_break ||
		    vnode->cb_v_break != vnode->volume->cb_v_break) {
			vnode->cb_s_break = vnode->cb_interest->server->cb_s_break;
			vnode->cb_v_break = vnode->volume->cb_v_break;
			valid = false;
		} else if (vnode->status.type == AFS_FTYPE_DIR &&
			   (!test_bit(AFS_VNODE_DIR_VALID, &vnode->flags) ||
			    vnode->cb_expires_at - 10 <= now)) {
			valid = false;
		} else if (test_bit(AFS_VNODE_ZAP_DATA, &vnode->flags) ||
			   vnode->cb_expires_at - 10 <= now) {
			valid = false;
		} else {
			valid = true;
		}
	} else if (test_bit(AFS_VNODE_DELETED, &vnode->flags)) {
		valid = true;
	} else {
		vnode->cb_v_break = vnode->volume->cb_v_break;
		valid = false;
	}

	read_sequnlock_excl(&vnode->cb_lock);

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
		ret = afs_fetch_status(vnode, key, false);
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