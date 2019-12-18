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
struct afs_vlserver {int dummy; } ;
struct afs_net {int dummy; } ;
struct afs_call {unsigned int server_index; int upgrade; int async; int /*<<< orphan*/ * request; int /*<<< orphan*/  max_lifespan; int /*<<< orphan*/  vlserver; struct key* key; } ;
struct afs_addr_cursor {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_PROBE_MAX_LIFESPAN ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct afs_call* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VLGETCAPABILITIES ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_RXVLGetCapabilities ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  afs_get_vlserver (struct afs_vlserver*) ; 
 int /*<<< orphan*/  afs_make_call (struct afs_addr_cursor*,struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_afs_make_vl_call (struct afs_call*) ; 

struct afs_call *afs_vl_get_capabilities(struct afs_net *net,
					 struct afs_addr_cursor *ac,
					 struct key *key,
					 struct afs_vlserver *server,
					 unsigned int server_index)
{
	struct afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(net, &afs_RXVLGetCapabilities, 1 * 4, 16 * 4);
	if (!call)
		return ERR_PTR(-ENOMEM);

	call->key = key;
	call->vlserver = afs_get_vlserver(server);
	call->server_index = server_index;
	call->upgrade = true;
	call->async = true;
	call->max_lifespan = AFS_PROBE_MAX_LIFESPAN;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(VLGETCAPABILITIES);

	/* Can't take a ref on server */
	trace_afs_make_vl_call(call);
	afs_make_call(ac, call, GFP_KERNEL);
	return call;
}