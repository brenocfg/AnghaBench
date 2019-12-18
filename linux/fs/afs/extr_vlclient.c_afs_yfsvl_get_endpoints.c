#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
struct in6_addr {int dummy; } ;
struct afs_vl_cursor {int /*<<< orphan*/  ac; int /*<<< orphan*/  key; TYPE_1__* cell; } ;
struct afs_net {int dummy; } ;
struct afs_call {int /*<<< orphan*/ * request; int /*<<< orphan*/  max_lifespan; int /*<<< orphan*/ * ret_alist; int /*<<< orphan*/  key; } ;
struct afs_addr_list {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct afs_net* net; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VL_MAX_LIFESPAN ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct afs_addr_list* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  YFS_SERVER_UUID ; 
 int /*<<< orphan*/  YVLGETENDPOINTS ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_YFSVLGetEndpoints ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  afs_make_call (int /*<<< orphan*/ *,struct afs_call*,int /*<<< orphan*/ ) ; 
 scalar_t__ afs_wait_for_call_to_complete (struct afs_call*,int /*<<< orphan*/ *) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  trace_afs_make_vl_call (struct afs_call*) ; 

struct afs_addr_list *afs_yfsvl_get_endpoints(struct afs_vl_cursor *vc,
					      const uuid_t *uuid)
{
	struct afs_call *call;
	struct afs_net *net = vc->cell->net;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(net, &afs_YFSVLGetEndpoints,
				   sizeof(__be32) * 2 + sizeof(*uuid),
				   sizeof(struct in6_addr) + sizeof(__be32) * 3);
	if (!call)
		return ERR_PTR(-ENOMEM);

	call->key = vc->key;
	call->ret_alist = NULL;
	call->max_lifespan = AFS_VL_MAX_LIFESPAN;

	/* Marshall the parameters */
	bp = call->request;
	*bp++ = htonl(YVLGETENDPOINTS);
	*bp++ = htonl(YFS_SERVER_UUID);
	memcpy(bp, uuid, sizeof(*uuid)); /* Type opr_uuid */

	trace_afs_make_vl_call(call);
	afs_make_call(&vc->ac, call, GFP_KERNEL);
	return (struct afs_addr_list *)afs_wait_for_call_to_complete(call, &vc->ac);
}