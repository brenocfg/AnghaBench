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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct ib_umad_rw_args {int /*<<< orphan*/  mgmt_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_NOEXIST ; 
 int* bpf_map_lookup_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_map_update_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_count ; 

int on_ib_umad_read_recv(struct ib_umad_rw_args *ctx)
{
	u64 zero = 0, *val;
	u8 class = ctx->mgmt_class;

	bpf_printk("ib_umad read recv : class 0x%x\n", class);

	val = bpf_map_lookup_elem(&read_count, &class);
	if (!val) {
		bpf_map_update_elem(&read_count, &class, &zero, BPF_NOEXIST);
		val = bpf_map_lookup_elem(&read_count, &class);
		if (!val)
			return 0;
	}

	(*val) += 1;

	return 0;
}