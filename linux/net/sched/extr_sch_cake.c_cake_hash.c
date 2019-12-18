#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  size_t u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_19__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_18__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_20__ {TYPE_8__ v6addrs; TYPE_7__ v4addrs; } ;
struct TYPE_17__ {int addr_type; } ;
struct TYPE_16__ {scalar_t__ flow_label; } ;
struct TYPE_15__ {scalar_t__ keyid; } ;
struct TYPE_14__ {scalar_t__ ip_proto; } ;
struct TYPE_13__ {scalar_t__ ports; } ;
struct flow_keys {TYPE_9__ addrs; TYPE_6__ control; TYPE_5__ tags; TYPE_4__ keyid; TYPE_3__ basic; TYPE_2__ ports; } ;
struct cake_tin_data {size_t* tags; TYPE_10__* flows; TYPE_1__* hosts; int /*<<< orphan*/  way_collisions; int /*<<< orphan*/  way_misses; int /*<<< orphan*/  way_hits; int /*<<< orphan*/  way_directs; } ;
struct TYPE_12__ {size_t srchost_tag; size_t dsthost_tag; int /*<<< orphan*/  dsthost_bulk_flow_count; int /*<<< orphan*/  srchost_bulk_flow_count; } ;
struct TYPE_11__ {scalar_t__ set; size_t srchost; size_t dsthost; } ;

/* Variables and functions */
 int CAKE_FLOW_DST_IP ; 
 int CAKE_FLOW_FLOWS ; 
 int CAKE_FLOW_HOSTS ; 
 int CAKE_FLOW_NAT_FLAG ; 
 int CAKE_FLOW_NONE ; 
 int CAKE_FLOW_SRC_IP ; 
 size_t CAKE_QUEUES ; 
 scalar_t__ CAKE_SET_BULK ; 
 size_t CAKE_SET_WAYS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL ; 
#define  FLOW_DISSECTOR_KEY_IPV4_ADDRS 129 
#define  FLOW_DISSECTOR_KEY_IPV6_ADDRS 128 
 int cake_ddst (int) ; 
 int cake_dsrc (int) ; 
 int /*<<< orphan*/  cake_update_flowkeys (struct flow_keys*,struct sk_buff const*) ; 
 size_t flow_hash_from_keys (struct flow_keys*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_flow_dissect_flow_keys (struct sk_buff const*,struct flow_keys*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32 cake_hash(struct cake_tin_data *q, const struct sk_buff *skb,
		     int flow_mode, u16 flow_override, u16 host_override)
{
	u32 flow_hash = 0, srchost_hash = 0, dsthost_hash = 0;
	u16 reduced_hash, srchost_idx, dsthost_idx;
	struct flow_keys keys, host_keys;

	if (unlikely(flow_mode == CAKE_FLOW_NONE))
		return 0;

	/* If both overrides are set we can skip packet dissection entirely */
	if ((flow_override || !(flow_mode & CAKE_FLOW_FLOWS)) &&
	    (host_override || !(flow_mode & CAKE_FLOW_HOSTS)))
		goto skip_hash;

	skb_flow_dissect_flow_keys(skb, &keys,
				   FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL);

	if (flow_mode & CAKE_FLOW_NAT_FLAG)
		cake_update_flowkeys(&keys, skb);

	/* flow_hash_from_keys() sorts the addresses by value, so we have
	 * to preserve their order in a separate data structure to treat
	 * src and dst host addresses as independently selectable.
	 */
	host_keys = keys;
	host_keys.ports.ports     = 0;
	host_keys.basic.ip_proto  = 0;
	host_keys.keyid.keyid     = 0;
	host_keys.tags.flow_label = 0;

	switch (host_keys.control.addr_type) {
	case FLOW_DISSECTOR_KEY_IPV4_ADDRS:
		host_keys.addrs.v4addrs.src = 0;
		dsthost_hash = flow_hash_from_keys(&host_keys);
		host_keys.addrs.v4addrs.src = keys.addrs.v4addrs.src;
		host_keys.addrs.v4addrs.dst = 0;
		srchost_hash = flow_hash_from_keys(&host_keys);
		break;

	case FLOW_DISSECTOR_KEY_IPV6_ADDRS:
		memset(&host_keys.addrs.v6addrs.src, 0,
		       sizeof(host_keys.addrs.v6addrs.src));
		dsthost_hash = flow_hash_from_keys(&host_keys);
		host_keys.addrs.v6addrs.src = keys.addrs.v6addrs.src;
		memset(&host_keys.addrs.v6addrs.dst, 0,
		       sizeof(host_keys.addrs.v6addrs.dst));
		srchost_hash = flow_hash_from_keys(&host_keys);
		break;

	default:
		dsthost_hash = 0;
		srchost_hash = 0;
	}

	/* This *must* be after the above switch, since as a
	 * side-effect it sorts the src and dst addresses.
	 */
	if (flow_mode & CAKE_FLOW_FLOWS)
		flow_hash = flow_hash_from_keys(&keys);

skip_hash:
	if (flow_override)
		flow_hash = flow_override - 1;
	if (host_override) {
		dsthost_hash = host_override - 1;
		srchost_hash = host_override - 1;
	}

	if (!(flow_mode & CAKE_FLOW_FLOWS)) {
		if (flow_mode & CAKE_FLOW_SRC_IP)
			flow_hash ^= srchost_hash;

		if (flow_mode & CAKE_FLOW_DST_IP)
			flow_hash ^= dsthost_hash;
	}

	reduced_hash = flow_hash % CAKE_QUEUES;

	/* set-associative hashing */
	/* fast path if no hash collision (direct lookup succeeds) */
	if (likely(q->tags[reduced_hash] == flow_hash &&
		   q->flows[reduced_hash].set)) {
		q->way_directs++;
	} else {
		u32 inner_hash = reduced_hash % CAKE_SET_WAYS;
		u32 outer_hash = reduced_hash - inner_hash;
		bool allocate_src = false;
		bool allocate_dst = false;
		u32 i, k;

		/* check if any active queue in the set is reserved for
		 * this flow.
		 */
		for (i = 0, k = inner_hash; i < CAKE_SET_WAYS;
		     i++, k = (k + 1) % CAKE_SET_WAYS) {
			if (q->tags[outer_hash + k] == flow_hash) {
				if (i)
					q->way_hits++;

				if (!q->flows[outer_hash + k].set) {
					/* need to increment host refcnts */
					allocate_src = cake_dsrc(flow_mode);
					allocate_dst = cake_ddst(flow_mode);
				}

				goto found;
			}
		}

		/* no queue is reserved for this flow, look for an
		 * empty one.
		 */
		for (i = 0; i < CAKE_SET_WAYS;
			 i++, k = (k + 1) % CAKE_SET_WAYS) {
			if (!q->flows[outer_hash + k].set) {
				q->way_misses++;
				allocate_src = cake_dsrc(flow_mode);
				allocate_dst = cake_ddst(flow_mode);
				goto found;
			}
		}

		/* With no empty queues, default to the original
		 * queue, accept the collision, update the host tags.
		 */
		q->way_collisions++;
		if (q->flows[outer_hash + k].set == CAKE_SET_BULK) {
			q->hosts[q->flows[reduced_hash].srchost].srchost_bulk_flow_count--;
			q->hosts[q->flows[reduced_hash].dsthost].dsthost_bulk_flow_count--;
		}
		allocate_src = cake_dsrc(flow_mode);
		allocate_dst = cake_ddst(flow_mode);
found:
		/* reserve queue for future packets in same flow */
		reduced_hash = outer_hash + k;
		q->tags[reduced_hash] = flow_hash;

		if (allocate_src) {
			srchost_idx = srchost_hash % CAKE_QUEUES;
			inner_hash = srchost_idx % CAKE_SET_WAYS;
			outer_hash = srchost_idx - inner_hash;
			for (i = 0, k = inner_hash; i < CAKE_SET_WAYS;
				i++, k = (k + 1) % CAKE_SET_WAYS) {
				if (q->hosts[outer_hash + k].srchost_tag ==
				    srchost_hash)
					goto found_src;
			}
			for (i = 0; i < CAKE_SET_WAYS;
				i++, k = (k + 1) % CAKE_SET_WAYS) {
				if (!q->hosts[outer_hash + k].srchost_bulk_flow_count)
					break;
			}
			q->hosts[outer_hash + k].srchost_tag = srchost_hash;
found_src:
			srchost_idx = outer_hash + k;
			if (q->flows[reduced_hash].set == CAKE_SET_BULK)
				q->hosts[srchost_idx].srchost_bulk_flow_count++;
			q->flows[reduced_hash].srchost = srchost_idx;
		}

		if (allocate_dst) {
			dsthost_idx = dsthost_hash % CAKE_QUEUES;
			inner_hash = dsthost_idx % CAKE_SET_WAYS;
			outer_hash = dsthost_idx - inner_hash;
			for (i = 0, k = inner_hash; i < CAKE_SET_WAYS;
			     i++, k = (k + 1) % CAKE_SET_WAYS) {
				if (q->hosts[outer_hash + k].dsthost_tag ==
				    dsthost_hash)
					goto found_dst;
			}
			for (i = 0; i < CAKE_SET_WAYS;
			     i++, k = (k + 1) % CAKE_SET_WAYS) {
				if (!q->hosts[outer_hash + k].dsthost_bulk_flow_count)
					break;
			}
			q->hosts[outer_hash + k].dsthost_tag = dsthost_hash;
found_dst:
			dsthost_idx = outer_hash + k;
			if (q->flows[reduced_hash].set == CAKE_SET_BULK)
				q->hosts[dsthost_idx].dsthost_bulk_flow_count++;
			q->flows[reduced_hash].dsthost = dsthost_idx;
		}
	}

	return reduced_hash;
}