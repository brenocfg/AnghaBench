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
typedef  int u64 ;
typedef  int u32 ;
struct netem_sched_data {int cell_size; int cell_overhead; int /*<<< orphan*/  rate; int /*<<< orphan*/  cell_size_reciprocal; scalar_t__ packet_overhead; } ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int div64_u64 (int,int /*<<< orphan*/ ) ; 
 int reciprocal_divide (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 packet_time_ns(u64 len, const struct netem_sched_data *q)
{
	len += q->packet_overhead;

	if (q->cell_size) {
		u32 cells = reciprocal_divide(len, q->cell_size_reciprocal);

		if (len > cells * q->cell_size)	/* extra cell needed for remainder */
			cells++;
		len = cells * (q->cell_size + q->cell_overhead);
	}

	return div64_u64(len * NSEC_PER_SEC, q->rate);
}