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
typedef  scalar_t__ uint64_t ;
struct __sk_buff {scalar_t__ tstamp; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ANY ; 
 int /*<<< orphan*/  BPF_EXIST ; 
 scalar_t__ ECN_HORIZON_NS ; 
 scalar_t__ NS_PER_SEC ; 
 int TC_ACT_OK ; 
 int TC_ACT_SHOT ; 
 scalar_t__ THROTTLE_RATE_BPS ; 
 scalar_t__ TIME_HORIZON_NS ; 
 scalar_t__ bpf_ktime_get_ns () ; 
 scalar_t__* bpf_map_lookup_elem (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ bpf_map_update_elem (int /*<<< orphan*/ *,int*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_skb_ecn_set_ce (struct __sk_buff*) ; 
 int /*<<< orphan*/  flow_map ; 

__attribute__((used)) static inline int throttle_flow(struct __sk_buff *skb)
{
	int key = 0;
	uint64_t *last_tstamp = bpf_map_lookup_elem(&flow_map, &key);
	uint64_t delay_ns = ((uint64_t)skb->len) * NS_PER_SEC /
			THROTTLE_RATE_BPS;
	uint64_t now = bpf_ktime_get_ns();
	uint64_t tstamp, next_tstamp = 0;

	if (last_tstamp)
		next_tstamp = *last_tstamp + delay_ns;

	tstamp = skb->tstamp;
	if (tstamp < now)
		tstamp = now;

	/* should we throttle? */
	if (next_tstamp <= tstamp) {
		if (bpf_map_update_elem(&flow_map, &key, &tstamp, BPF_ANY))
			return TC_ACT_SHOT;
		return TC_ACT_OK;
	}

	/* do not queue past the time horizon */
	if (next_tstamp - now >= TIME_HORIZON_NS)
		return TC_ACT_SHOT;

	/* set ecn bit, if needed */
	if (next_tstamp - now >= ECN_HORIZON_NS)
		bpf_skb_ecn_set_ce(skb);

	if (bpf_map_update_elem(&flow_map, &key, &next_tstamp, BPF_EXIST))
		return TC_ACT_SHOT;
	skb->tstamp = next_tstamp;

	return TC_ACT_OK;
}