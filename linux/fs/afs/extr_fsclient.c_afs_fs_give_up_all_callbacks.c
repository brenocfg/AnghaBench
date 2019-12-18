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
struct afs_server {int dummy; } ;
struct afs_net {int dummy; } ;
struct afs_call {int /*<<< orphan*/ * request; struct key* key; } ;
struct afs_addr_cursor {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FSGIVEUPALLCALLBACKS ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_RXFSGiveUpAllCallBacks ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_make_call (struct afs_addr_cursor*,struct afs_call*,int /*<<< orphan*/ ) ; 
 int afs_wait_for_call_to_complete (struct afs_call*,struct afs_addr_cursor*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 

int afs_fs_give_up_all_callbacks(struct afs_net *net,
				 struct afs_server *server,
				 struct afs_addr_cursor *ac,
				 struct key *key)
{
	struct afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(net, &afs_RXFSGiveUpAllCallBacks, 1 * 4, 0);
	if (!call)
		return -ENOMEM;

	call->key = key;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSGIVEUPALLCALLBACKS);

	/* Can't take a ref on server */
	afs_make_call(ac, call, GFP_NOFS);
	return afs_wait_for_call_to_complete(call, ac);
}