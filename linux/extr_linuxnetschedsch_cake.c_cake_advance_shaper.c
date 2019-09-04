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
typedef  int u64 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct cake_tin_data {int tin_rate_ns; int tin_rate_shft; void* time_next_packet; } ;
struct cake_sched_data {int rate_ns; int rate_shft; void* time_next_packet; void* failsafe_next_packet; } ;
typedef  void* ktime_t ;
struct TYPE_2__ {int adjusted_len; } ;

/* Variables and functions */
 TYPE_1__* get_cobalt_cb (struct sk_buff*) ; 
 void* ktime_add_ns (void*,int) ; 
 scalar_t__ ktime_before (void*,void*) ; 

__attribute__((used)) static int cake_advance_shaper(struct cake_sched_data *q,
			       struct cake_tin_data *b,
			       struct sk_buff *skb,
			       ktime_t now, bool drop)
{
	u32 len = get_cobalt_cb(skb)->adjusted_len;

	/* charge packet bandwidth to this tin
	 * and to the global shaper.
	 */
	if (q->rate_ns) {
		u64 tin_dur = (len * b->tin_rate_ns) >> b->tin_rate_shft;
		u64 global_dur = (len * q->rate_ns) >> q->rate_shft;
		u64 failsafe_dur = global_dur + (global_dur >> 1);

		if (ktime_before(b->time_next_packet, now))
			b->time_next_packet = ktime_add_ns(b->time_next_packet,
							   tin_dur);

		else if (ktime_before(b->time_next_packet,
				      ktime_add_ns(now, tin_dur)))
			b->time_next_packet = ktime_add_ns(now, tin_dur);

		q->time_next_packet = ktime_add_ns(q->time_next_packet,
						   global_dur);
		if (!drop)
			q->failsafe_next_packet = \
				ktime_add_ns(q->failsafe_next_packet,
					     failsafe_dur);
	}
	return len;
}