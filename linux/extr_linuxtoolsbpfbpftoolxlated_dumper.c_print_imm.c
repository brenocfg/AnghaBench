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
struct dump_data {char const* scratch_buff; } ;
struct bpf_insn {scalar_t__ src_reg; unsigned long long imm; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 scalar_t__ BPF_PSEUDO_MAP_FD ; 
 int /*<<< orphan*/  snprintf (char const*,int,char*,unsigned long long) ; 

__attribute__((used)) static const char *print_imm(void *private_data,
			     const struct bpf_insn *insn,
			     __u64 full_imm)
{
	struct dump_data *dd = private_data;

	if (insn->src_reg == BPF_PSEUDO_MAP_FD)
		snprintf(dd->scratch_buff, sizeof(dd->scratch_buff),
			 "map[id:%u]", insn->imm);
	else
		snprintf(dd->scratch_buff, sizeof(dd->scratch_buff),
			 "0x%llx", (unsigned long long)full_imm);
	return dd->scratch_buff;
}