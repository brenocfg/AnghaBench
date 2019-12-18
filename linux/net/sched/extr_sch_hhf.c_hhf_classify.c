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
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct hhf_sched_data {size_t hhf_arrays_reset_timestamp; size_t hhf_reset_timeout; size_t** hhf_arrays; size_t hhf_admit_bytes; int /*<<< orphan*/  hh_flows_total_cnt; int /*<<< orphan*/ * hh_flows; int /*<<< orphan*/ * hhf_valid_bits; int /*<<< orphan*/  perturbation; } ;
struct hh_flow_state {size_t hit_timestamp; size_t hash_id; } ;
struct Qdisc {int dummy; } ;
typedef  enum wdrr_bucket_idx { ____Placeholder_wdrr_bucket_idx } wdrr_bucket_idx ;

/* Variables and functions */
 int HHF_ARRAYS_CNT ; 
 int /*<<< orphan*/  HHF_ARRAYS_LEN ; 
 size_t HHF_BIT_MASK ; 
 size_t HHF_BIT_MASK_LEN ; 
 int WDRR_BUCKET_FOR_HH ; 
 int WDRR_BUCKET_FOR_NON_HH ; 
 int /*<<< orphan*/  __set_bit (size_t,int /*<<< orphan*/ ) ; 
 struct hh_flow_state* alloc_new_hh (int /*<<< orphan*/ *,struct hhf_sched_data*) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hhf_time_before (size_t,size_t) ; 
 size_t hhf_time_stamp () ; 
 size_t qdisc_pkt_len (struct sk_buff*) ; 
 struct hhf_sched_data* qdisc_priv (struct Qdisc*) ; 
 struct hh_flow_state* seek_list (size_t,int /*<<< orphan*/ *,struct hhf_sched_data*) ; 
 size_t skb_get_hash_perturb (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum wdrr_bucket_idx hhf_classify(struct sk_buff *skb, struct Qdisc *sch)
{
	struct hhf_sched_data *q = qdisc_priv(sch);
	u32 tmp_hash, hash;
	u32 xorsum, filter_pos[HHF_ARRAYS_CNT], flow_pos;
	struct hh_flow_state *flow;
	u32 pkt_len, min_hhf_val;
	int i;
	u32 prev;
	u32 now = hhf_time_stamp();

	/* Reset the HHF counter arrays if this is the right time. */
	prev = q->hhf_arrays_reset_timestamp + q->hhf_reset_timeout;
	if (hhf_time_before(prev, now)) {
		for (i = 0; i < HHF_ARRAYS_CNT; i++)
			bitmap_zero(q->hhf_valid_bits[i], HHF_ARRAYS_LEN);
		q->hhf_arrays_reset_timestamp = now;
	}

	/* Get hashed flow-id of the skb. */
	hash = skb_get_hash_perturb(skb, &q->perturbation);

	/* Check if this packet belongs to an already established HH flow. */
	flow_pos = hash & HHF_BIT_MASK;
	flow = seek_list(hash, &q->hh_flows[flow_pos], q);
	if (flow) { /* found its HH flow */
		flow->hit_timestamp = now;
		return WDRR_BUCKET_FOR_HH;
	}

	/* Now pass the packet through the multi-stage filter. */
	tmp_hash = hash;
	xorsum = 0;
	for (i = 0; i < HHF_ARRAYS_CNT - 1; i++) {
		/* Split the skb_hash into three 10-bit chunks. */
		filter_pos[i] = tmp_hash & HHF_BIT_MASK;
		xorsum ^= filter_pos[i];
		tmp_hash >>= HHF_BIT_MASK_LEN;
	}
	/* The last chunk is computed as XOR sum of other chunks. */
	filter_pos[HHF_ARRAYS_CNT - 1] = xorsum ^ tmp_hash;

	pkt_len = qdisc_pkt_len(skb);
	min_hhf_val = ~0U;
	for (i = 0; i < HHF_ARRAYS_CNT; i++) {
		u32 val;

		if (!test_bit(filter_pos[i], q->hhf_valid_bits[i])) {
			q->hhf_arrays[i][filter_pos[i]] = 0;
			__set_bit(filter_pos[i], q->hhf_valid_bits[i]);
		}

		val = q->hhf_arrays[i][filter_pos[i]] + pkt_len;
		if (min_hhf_val > val)
			min_hhf_val = val;
	}

	/* Found a new HH iff all counter values > HH admit threshold. */
	if (min_hhf_val > q->hhf_admit_bytes) {
		/* Just captured a new heavy-hitter. */
		flow = alloc_new_hh(&q->hh_flows[flow_pos], q);
		if (!flow) /* memory alloc problem */
			return WDRR_BUCKET_FOR_NON_HH;
		flow->hash_id = hash;
		flow->hit_timestamp = now;
		q->hh_flows_total_cnt++;

		/* By returning without updating counters in q->hhf_arrays,
		 * we implicitly implement "shielding" (see Optimization O1).
		 */
		return WDRR_BUCKET_FOR_HH;
	}

	/* Conservative update of HHF arrays (see Optimization O2). */
	for (i = 0; i < HHF_ARRAYS_CNT; i++) {
		if (q->hhf_arrays[i][filter_pos[i]] < min_hhf_val)
			q->hhf_arrays[i][filter_pos[i]] = min_hhf_val;
	}
	return WDRR_BUCKET_FOR_NON_HH;
}