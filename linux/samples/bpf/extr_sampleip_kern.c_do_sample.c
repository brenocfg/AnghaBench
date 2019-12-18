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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct bpf_perf_event_data {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_NOEXIST ; 
 int /*<<< orphan*/  PT_REGS_IP (int /*<<< orphan*/ *) ; 
 int* bpf_map_lookup_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_map_update_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_map ; 

int do_sample(struct bpf_perf_event_data *ctx)
{
	u64 ip;
	u32 *value, init_val = 1;

	ip = PT_REGS_IP(&ctx->regs);
	value = bpf_map_lookup_elem(&ip_map, &ip);
	if (value)
		*value += 1;
	else
		/* E2BIG not tested for this example only */
		bpf_map_update_elem(&ip_map, &ip, &init_val, BPF_NOEXIST);

	return 0;
}