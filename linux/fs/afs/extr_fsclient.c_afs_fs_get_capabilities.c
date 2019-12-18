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
struct afs_call {unsigned int server_index; int upgrade; int async; int /*<<< orphan*/ * request; int /*<<< orphan*/  max_lifespan; int /*<<< orphan*/  server; struct key* key; } ;
struct afs_addr_cursor {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_PROBE_MAX_LIFESPAN ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct afs_call* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSGETCAPABILITIES ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_RXFSGetCapabilities ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  afs_get_server (struct afs_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_make_call (struct afs_addr_cursor*,struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_server_trace_get_caps ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_afs_make_fs_call (struct afs_call*,int /*<<< orphan*/ *) ; 

struct afs_call *afs_fs_get_capabilities(struct afs_net *net,
					 struct afs_server *server,
					 struct afs_addr_cursor *ac,
					 struct key *key,
					 unsigned int server_index)
{
	struct afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(net, &afs_RXFSGetCapabilities, 1 * 4, 16 * 4);
	if (!call)
		return ERR_PTR(-ENOMEM);

	call->key = key;
	call->server = afs_get_server(server, afs_server_trace_get_caps);
	call->server_index = server_index;
	call->upgrade = true;
	call->async = true;
	call->max_lifespan = AFS_PROBE_MAX_LIFESPAN;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSGETCAPABILITIES);

	/* Can't take a ref on server */
	trace_afs_make_fs_call(call, NULL);
	afs_make_call(ac, call, GFP_NOFS);
	return call;
}