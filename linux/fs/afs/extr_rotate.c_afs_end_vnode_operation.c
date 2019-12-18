#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct afs_net {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  abort_code; } ;
struct afs_fs_cursor {int error; TYPE_2__ ac; int /*<<< orphan*/  server_list; int /*<<< orphan*/  cbi; TYPE_1__* vnode; } ;
struct TYPE_3__ {int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int ECONNABORTED ; 
 int EDESTADDRREQ ; 
 int EHOSTUNREACH ; 
 int ENETUNREACH ; 
 int afs_abort_to_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_dump_edestaddrreq (struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_end_cursor (TYPE_2__*) ; 
 int /*<<< orphan*/  afs_put_cb_interest (struct afs_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_put_serverlist (struct afs_net*,int /*<<< orphan*/ ) ; 
 struct afs_net* afs_v2net (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int afs_end_vnode_operation(struct afs_fs_cursor *fc)
{
	struct afs_net *net = afs_v2net(fc->vnode);

	if (fc->error == -EDESTADDRREQ ||
	    fc->error == -EADDRNOTAVAIL ||
	    fc->error == -ENETUNREACH ||
	    fc->error == -EHOSTUNREACH)
		afs_dump_edestaddrreq(fc);

	mutex_unlock(&fc->vnode->io_lock);

	afs_end_cursor(&fc->ac);
	afs_put_cb_interest(net, fc->cbi);
	afs_put_serverlist(net, fc->server_list);

	if (fc->error == -ECONNABORTED)
		fc->error = afs_abort_to_error(fc->ac.abort_code);

	return fc->error;
}