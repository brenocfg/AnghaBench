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
typedef  int /*<<< orphan*/  uuid_t ;
struct afs_vl_cursor {int /*<<< orphan*/  ac; int /*<<< orphan*/  key; TYPE_1__* cell; } ;
struct afs_uuid__xdr {int dummy; } ;
struct afs_uuid {int /*<<< orphan*/ * node; int /*<<< orphan*/  clock_seq_low; int /*<<< orphan*/  clock_seq_hi_and_reserved; int /*<<< orphan*/  time_hi_and_version; int /*<<< orphan*/  time_mid; int /*<<< orphan*/  time_low; } ;
struct afs_net {int dummy; } ;
struct afs_call {int /*<<< orphan*/ * request; int /*<<< orphan*/  max_lifespan; int /*<<< orphan*/ * ret_alist; int /*<<< orphan*/  key; } ;
struct afs_addr_list {int dummy; } ;
struct TYPE_4__ {void** node; void* clock_seq_low; void* clock_seq_hi_and_reserved; void* time_hi_and_version; void* time_mid; int /*<<< orphan*/  time_low; } ;
struct afs_ListAddrByAttributes__xdr {TYPE_2__ uuid; scalar_t__ spare; scalar_t__ index; scalar_t__ ipaddr; void* Mask; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {struct afs_net* net; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VLADDR_UUID ; 
 int /*<<< orphan*/  AFS_VL_MAX_LIFESPAN ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct afs_addr_list* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VLGETADDRSU ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_RXVLGetAddrsU ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  afs_make_call (int /*<<< orphan*/ *,struct afs_call*,int /*<<< orphan*/ ) ; 
 scalar_t__ afs_wait_for_call_to_complete (struct afs_call*,int /*<<< orphan*/ *) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_afs_make_vl_call (struct afs_call*) ; 

struct afs_addr_list *afs_vl_get_addrs_u(struct afs_vl_cursor *vc,
					 const uuid_t *uuid)
{
	struct afs_ListAddrByAttributes__xdr *r;
	const struct afs_uuid *u = (const struct afs_uuid *)uuid;
	struct afs_call *call;
	struct afs_net *net = vc->cell->net;
	__be32 *bp;
	int i;

	_enter("");

	call = afs_alloc_flat_call(net, &afs_RXVLGetAddrsU,
				   sizeof(__be32) + sizeof(struct afs_ListAddrByAttributes__xdr),
				   sizeof(struct afs_uuid__xdr) + 3 * sizeof(__be32));
	if (!call)
		return ERR_PTR(-ENOMEM);

	call->key = vc->key;
	call->ret_alist = NULL;
	call->max_lifespan = AFS_VL_MAX_LIFESPAN;

	/* Marshall the parameters */
	bp = call->request;
	*bp++ = htonl(VLGETADDRSU);
	r = (struct afs_ListAddrByAttributes__xdr *)bp;
	r->Mask		= htonl(AFS_VLADDR_UUID);
	r->ipaddr	= 0;
	r->index	= 0;
	r->spare	= 0;
	r->uuid.time_low			= u->time_low;
	r->uuid.time_mid			= htonl(ntohs(u->time_mid));
	r->uuid.time_hi_and_version		= htonl(ntohs(u->time_hi_and_version));
	r->uuid.clock_seq_hi_and_reserved 	= htonl(u->clock_seq_hi_and_reserved);
	r->uuid.clock_seq_low			= htonl(u->clock_seq_low);
	for (i = 0; i < 6; i++)
		r->uuid.node[i] = htonl(u->node[i]);

	trace_afs_make_vl_call(call);
	afs_make_call(&vc->ac, call, GFP_KERNEL);
	return (struct afs_addr_list *)afs_wait_for_call_to_complete(call, &vc->ac);
}