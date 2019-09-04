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
struct key {int dummy; } ;
struct TYPE_10__ {int anon_access; int caller_access; } ;
struct TYPE_6__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {TYPE_5__ status; int /*<<< orphan*/  permit_cache; TYPE_3__* volume; TYPE_1__ fid; } ;
struct afs_permits {int nr_permits; int /*<<< orphan*/  invalidated; TYPE_4__* permits; } ;
typedef  int afs_access_t ;
struct TYPE_9__ {int access; struct key* key; } ;
struct TYPE_8__ {TYPE_2__* cell; } ;
struct TYPE_7__ {struct key* anonymous_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int afs_fetch_status (struct afs_vnode*,struct key*,int) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 struct afs_permits* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int afs_check_permit(struct afs_vnode *vnode, struct key *key,
		     afs_access_t *_access)
{
	struct afs_permits *permits;
	bool valid = false;
	int i, ret;

	_enter("{%x:%u},%x",
	       vnode->fid.vid, vnode->fid.vnode, key_serial(key));

	/* check the permits to see if we've got one yet */
	if (key == vnode->volume->cell->anonymous_key) {
		_debug("anon");
		*_access = vnode->status.anon_access;
		valid = true;
	} else {
		rcu_read_lock();
		permits = rcu_dereference(vnode->permit_cache);
		if (permits) {
			for (i = 0; i < permits->nr_permits; i++) {
				if (permits->permits[i].key < key)
					continue;
				if (permits->permits[i].key > key)
					break;

				*_access = permits->permits[i].access;
				valid = !permits->invalidated;
				break;
			}
		}
		rcu_read_unlock();
	}

	if (!valid) {
		/* Check the status on the file we're actually interested in
		 * (the post-processing will cache the result).
		 */
		_debug("no valid permit");

		ret = afs_fetch_status(vnode, key, false);
		if (ret < 0) {
			*_access = 0;
			_leave(" = %d", ret);
			return ret;
		}
		*_access = vnode->status.caller_access;
	}

	_leave(" = 0 [access %x]", *_access);
	return 0;
}