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
struct nf_flow_route {TYPE_2__* tuple; } ;
struct TYPE_3__ {int /*<<< orphan*/  use; } ;
struct nf_conn {int status; TYPE_1__ ct_general; } ;
struct flow_offload {int /*<<< orphan*/  flags; } ;
struct flow_offload_entry {struct nf_conn* ct; struct flow_offload flow; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 size_t FLOW_OFFLOAD_DIR_ORIGINAL ; 
 size_t FLOW_OFFLOAD_DIR_REPLY ; 
 int /*<<< orphan*/  FLOW_OFFLOAD_DNAT ; 
 int /*<<< orphan*/  FLOW_OFFLOAD_SNAT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IPS_DST_NAT ; 
 int IPS_SRC_NAT ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_hold_safe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_offload_fill_dir (struct flow_offload*,struct nf_conn*,struct nf_flow_route*,size_t) ; 
 int /*<<< orphan*/  kfree (struct flow_offload_entry*) ; 
 struct flow_offload_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nf_ct_is_dying (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 scalar_t__ unlikely (int) ; 

struct flow_offload *
flow_offload_alloc(struct nf_conn *ct, struct nf_flow_route *route)
{
	struct flow_offload_entry *entry;
	struct flow_offload *flow;

	if (unlikely(nf_ct_is_dying(ct) ||
	    !atomic_inc_not_zero(&ct->ct_general.use)))
		return NULL;

	entry = kzalloc(sizeof(*entry), GFP_ATOMIC);
	if (!entry)
		goto err_ct_refcnt;

	flow = &entry->flow;

	if (!dst_hold_safe(route->tuple[FLOW_OFFLOAD_DIR_ORIGINAL].dst))
		goto err_dst_cache_original;

	if (!dst_hold_safe(route->tuple[FLOW_OFFLOAD_DIR_REPLY].dst))
		goto err_dst_cache_reply;

	entry->ct = ct;

	flow_offload_fill_dir(flow, ct, route, FLOW_OFFLOAD_DIR_ORIGINAL);
	flow_offload_fill_dir(flow, ct, route, FLOW_OFFLOAD_DIR_REPLY);

	if (ct->status & IPS_SRC_NAT)
		flow->flags |= FLOW_OFFLOAD_SNAT;
	if (ct->status & IPS_DST_NAT)
		flow->flags |= FLOW_OFFLOAD_DNAT;

	return flow;

err_dst_cache_reply:
	dst_release(route->tuple[FLOW_OFFLOAD_DIR_ORIGINAL].dst);
err_dst_cache_original:
	kfree(entry);
err_ct_refcnt:
	nf_ct_put(ct);

	return NULL;
}