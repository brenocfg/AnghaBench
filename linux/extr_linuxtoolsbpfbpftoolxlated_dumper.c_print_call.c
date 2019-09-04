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
struct kernel_sym {int dummy; } ;
struct dump_data {unsigned long address_call_base; scalar_t__ nr_jited_ksyms; unsigned long* jited_ksyms; } ;
struct bpf_insn {unsigned long imm; scalar_t__ src_reg; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ BPF_PSEUDO_CALL ; 
 struct kernel_sym* kernel_syms_search (struct dump_data*,unsigned long) ; 
 char const* print_call_helper (struct dump_data*,struct kernel_sym*,unsigned long) ; 
 char const* print_call_pcrel (struct dump_data*,struct kernel_sym*,unsigned long,struct bpf_insn const*) ; 

__attribute__((used)) static const char *print_call(void *private_data,
			      const struct bpf_insn *insn)
{
	struct dump_data *dd = private_data;
	unsigned long address = dd->address_call_base + insn->imm;
	struct kernel_sym *sym;

	if (insn->src_reg == BPF_PSEUDO_CALL &&
	    (__u32) insn->imm < dd->nr_jited_ksyms)
		address = dd->jited_ksyms[insn->imm];

	sym = kernel_syms_search(dd, address);
	if (insn->src_reg == BPF_PSEUDO_CALL)
		return print_call_pcrel(dd, sym, address, insn);
	else
		return print_call_helper(dd, sym, address);
}