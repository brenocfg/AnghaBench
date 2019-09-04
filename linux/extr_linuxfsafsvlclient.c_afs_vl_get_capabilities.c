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
struct afs_net {int dummy; } ;
struct afs_call {int upgrade; int ret_reply0; int /*<<< orphan*/ * request; void** reply; struct key* key; } ;
struct afs_addr_cursor {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ VLGETCAPABILITIES ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_RXVLGetCapabilities ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 int afs_make_call (struct afs_addr_cursor*,struct afs_call*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int /*<<< orphan*/  trace_afs_make_vl_call (struct afs_call*) ; 

int afs_vl_get_capabilities(struct afs_net *net,
			    struct afs_addr_cursor *ac,
			    struct key *key)
{
	struct afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(net, &afs_RXVLGetCapabilities, 1 * 4, 16 * 4);
	if (!call)
		return -ENOMEM;

	call->key = key;
	call->upgrade = true; /* Let's see if this is a YFS server */
	call->reply[0] = (void *)VLGETCAPABILITIES;
	call->ret_reply0 = true;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(VLGETCAPABILITIES);

	/* Can't take a ref on server */
	trace_afs_make_vl_call(call);
	return afs_make_call(ac, call, GFP_KERNEL, false);
}