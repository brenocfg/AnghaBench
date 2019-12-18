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
typedef  long long u64 ;
typedef  int u32 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 long PT_REGS_PARM1 (struct pt_regs*) ; 
 int SLOTS ; 
 long long bpf_ktime_get_ns () ; 
 int /*<<< orphan*/  bpf_map_delete_elem (int /*<<< orphan*/ *,long*) ; 
 long long* bpf_map_lookup_elem (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  lat_map ; 
 long long log2l (long long) ; 
 int /*<<< orphan*/  my_map ; 

int bpf_prog2(struct pt_regs *ctx)
{
	long rq = PT_REGS_PARM1(ctx);
	u64 *value, l, base;
	u32 index;

	value = bpf_map_lookup_elem(&my_map, &rq);
	if (!value)
		return 0;

	u64 cur_time = bpf_ktime_get_ns();
	u64 delta = cur_time - *value;

	bpf_map_delete_elem(&my_map, &rq);

	/* the lines below are computing index = log10(delta)*10
	 * using integer arithmetic
	 * index = 29 ~ 1 usec
	 * index = 59 ~ 1 msec
	 * index = 89 ~ 1 sec
	 * index = 99 ~ 10sec or more
	 * log10(x)*10 = log2(x)*10/log2(10) = log2(x)*3
	 */
	l = log2l(delta);
	base = 1ll << l;
	index = (l * 64 + (delta - base) * 64 / base) * 3 / 64;

	if (index >= SLOTS)
		index = SLOTS - 1;

	value = bpf_map_lookup_elem(&lat_map, &index);
	if (value)
		*value += 1;

	return 0;
}