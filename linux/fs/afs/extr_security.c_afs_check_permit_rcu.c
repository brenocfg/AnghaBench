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
struct TYPE_9__ {int /*<<< orphan*/  anon_access; } ;
struct TYPE_6__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {int /*<<< orphan*/  permit_cache; TYPE_4__ status; TYPE_3__* volume; TYPE_1__ fid; } ;
struct afs_permits {int nr_permits; int /*<<< orphan*/  invalidated; TYPE_5__* permits; } ;
typedef  int /*<<< orphan*/  afs_access_t ;
struct TYPE_10__ {int /*<<< orphan*/  access; struct key* key; } ;
struct TYPE_8__ {TYPE_2__* cell; } ;
struct TYPE_7__ {struct key* anonymous_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 struct afs_permits* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool afs_check_permit_rcu(struct afs_vnode *vnode, struct key *key,
				 afs_access_t *_access)
{
	const struct afs_permits *permits;
	int i;

	_enter("{%llx:%llu},%x",
	       vnode->fid.vid, vnode->fid.vnode, key_serial(key));

	/* check the permits to see if we've got one yet */
	if (key == vnode->volume->cell->anonymous_key) {
		*_access = vnode->status.anon_access;
		_leave(" = t [anon %x]", *_access);
		return true;
	}

	permits = rcu_dereference(vnode->permit_cache);
	if (permits) {
		for (i = 0; i < permits->nr_permits; i++) {
			if (permits->permits[i].key < key)
				continue;
			if (permits->permits[i].key > key)
				break;

			*_access = permits->permits[i].access;
			_leave(" = %u [perm %x]", !permits->invalidated, *_access);
			return !permits->invalidated;
		}
	}

	_leave(" = f");
	return false;
}