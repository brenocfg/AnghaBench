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
struct bpf_prog_info_linear {unsigned long arrays; int /*<<< orphan*/  info; int /*<<< orphan*/  data; } ;
struct bpf_prog_info_array_desc {int /*<<< orphan*/  array_offset; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int BPF_PROG_INFO_FIRST_ARRAY ; 
 int BPF_PROG_INFO_LAST_ARRAY ; 
 struct bpf_prog_info_array_desc* bpf_prog_info_array_desc ; 
 scalar_t__ bpf_prog_info_read_offset_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_info_set_offset_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ptr_to_u64 (int /*<<< orphan*/ ) ; 

void bpf_program__bpil_addr_to_offs(struct bpf_prog_info_linear *info_linear)
{
	int i;

	for (i = BPF_PROG_INFO_FIRST_ARRAY; i < BPF_PROG_INFO_LAST_ARRAY; ++i) {
		struct bpf_prog_info_array_desc *desc;
		__u64 addr, offs;

		if ((info_linear->arrays & (1UL << i)) == 0)
			continue;

		desc = bpf_prog_info_array_desc + i;
		addr = bpf_prog_info_read_offset_u64(&info_linear->info,
						     desc->array_offset);
		offs = addr - ptr_to_u64(info_linear->data);
		bpf_prog_info_set_offset_u64(&info_linear->info,
					     desc->array_offset, offs);
	}
}