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
typedef  int /*<<< orphan*/  uuid_t ;
struct key {int dummy; } ;
struct in6_addr {int dummy; } ;
struct afs_net {int dummy; } ;
struct afs_call {int ret_reply0; int /*<<< orphan*/ * request; int /*<<< orphan*/ ** reply; struct key* key; } ;
struct afs_addr_list {int dummy; } ;
struct afs_addr_cursor {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct afs_addr_list* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  YFS_SERVER_UUID ; 
 int /*<<< orphan*/  YVLGETENDPOINTS ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_YFSVLGetEndpoints ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ afs_make_call (struct afs_addr_cursor*,struct afs_call*,int /*<<< orphan*/ ,int) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  trace_afs_make_vl_call (struct afs_call*) ; 

struct afs_addr_list *afs_yfsvl_get_endpoints(struct afs_net *net,
					      struct afs_addr_cursor *ac,
					      struct key *key,
					      const uuid_t *uuid)
{
	struct afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(net, &afs_YFSVLGetEndpoints,
				   sizeof(__be32) * 2 + sizeof(*uuid),
				   sizeof(struct in6_addr) + sizeof(__be32) * 3);
	if (!call)
		return ERR_PTR(-ENOMEM);

	call->key = key;
	call->reply[0] = NULL;
	call->ret_reply0 = true;

	/* Marshall the parameters */
	bp = call->request;
	*bp++ = htonl(YVLGETENDPOINTS);
	*bp++ = htonl(YFS_SERVER_UUID);
	memcpy(bp, uuid, sizeof(*uuid)); /* Type opr_uuid */

	trace_afs_make_vl_call(call);
	return (struct afs_addr_list *)afs_make_call(ac, call, GFP_KERNEL, false);
}