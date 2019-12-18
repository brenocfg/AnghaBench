#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct afs_vnode {TYPE_2__ cb_lock; int /*<<< orphan*/  flags; TYPE_1__* volume; int /*<<< orphan*/  cb_v_break; int /*<<< orphan*/  cb_s_break; int /*<<< orphan*/  cb_interest; int /*<<< orphan*/  io_lock; } ;
struct afs_server_list {int /*<<< orphan*/  lock; struct afs_server_entry* servers; } ;
struct afs_server_entry {struct afs_cb_interest* cb_interest; struct afs_server* server; } ;
struct afs_server {int /*<<< orphan*/  cb_s_break; } ;
struct afs_cb_interest {struct afs_server* server; } ;
struct TYPE_4__ {int /*<<< orphan*/  cb_v_break; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VNODE_CB_PROMISED ; 
 int /*<<< orphan*/  ASSERT (struct afs_cb_interest*) ; 
 int ENOMEM ; 
 struct afs_cb_interest* afs_create_interest (struct afs_server*,struct afs_vnode*) ; 
 void* afs_get_cb_interest (struct afs_cb_interest*) ; 
 int /*<<< orphan*/  afs_put_cb_interest (int /*<<< orphan*/ ,struct afs_cb_interest*) ; 
 int /*<<< orphan*/  afs_v2net (struct afs_vnode*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct afs_cb_interest*) ; 
 struct afs_cb_interest* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqlock (TYPE_2__*) ; 
 int /*<<< orphan*/  write_sequnlock (TYPE_2__*) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int afs_register_server_cb_interest(struct afs_vnode *vnode,
				    struct afs_server_list *slist,
				    unsigned int index)
{
	struct afs_server_entry *entry = &slist->servers[index];
	struct afs_cb_interest *cbi, *vcbi, *new, *old;
	struct afs_server *server = entry->server;

again:
	vcbi = rcu_dereference_protected(vnode->cb_interest,
					 lockdep_is_held(&vnode->io_lock));
	if (vcbi && likely(vcbi == entry->cb_interest))
		return 0;

	read_lock(&slist->lock);
	cbi = afs_get_cb_interest(entry->cb_interest);
	read_unlock(&slist->lock);

	if (vcbi) {
		if (vcbi == cbi) {
			afs_put_cb_interest(afs_v2net(vnode), cbi);
			return 0;
		}

		/* Use a new interest in the server list for the same server
		 * rather than an old one that's still attached to a vnode.
		 */
		if (cbi && vcbi->server == cbi->server) {
			write_seqlock(&vnode->cb_lock);
			old = rcu_dereference_protected(vnode->cb_interest,
							lockdep_is_held(&vnode->cb_lock.lock));
			rcu_assign_pointer(vnode->cb_interest, cbi);
			write_sequnlock(&vnode->cb_lock);
			afs_put_cb_interest(afs_v2net(vnode), old);
			return 0;
		}

		/* Re-use the one attached to the vnode. */
		if (!cbi && vcbi->server == server) {
			write_lock(&slist->lock);
			if (entry->cb_interest) {
				write_unlock(&slist->lock);
				afs_put_cb_interest(afs_v2net(vnode), cbi);
				goto again;
			}

			entry->cb_interest = cbi;
			write_unlock(&slist->lock);
			return 0;
		}
	}

	if (!cbi) {
		new = afs_create_interest(server, vnode);
		if (!new)
			return -ENOMEM;

		write_lock(&slist->lock);
		if (!entry->cb_interest) {
			entry->cb_interest = afs_get_cb_interest(new);
			cbi = new;
			new = NULL;
		} else {
			cbi = afs_get_cb_interest(entry->cb_interest);
		}
		write_unlock(&slist->lock);
		afs_put_cb_interest(afs_v2net(vnode), new);
	}

	ASSERT(cbi);

	/* Change the server the vnode is using.  This entails scrubbing any
	 * interest the vnode had in the previous server it was using.
	 */
	write_seqlock(&vnode->cb_lock);

	old = rcu_dereference_protected(vnode->cb_interest,
					lockdep_is_held(&vnode->cb_lock.lock));
	rcu_assign_pointer(vnode->cb_interest, cbi);
	vnode->cb_s_break = cbi->server->cb_s_break;
	vnode->cb_v_break = vnode->volume->cb_v_break;
	clear_bit(AFS_VNODE_CB_PROMISED, &vnode->flags);

	write_sequnlock(&vnode->cb_lock);
	afs_put_cb_interest(afs_v2net(vnode), old);
	return 0;
}