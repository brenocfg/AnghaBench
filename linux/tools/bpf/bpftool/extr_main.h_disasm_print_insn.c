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
struct btf {int dummy; } ;
struct bpf_prog_linfo {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */

__attribute__((used)) static inline
void disasm_print_insn(unsigned char *image, ssize_t len, int opcodes,
		       const char *arch, const char *disassembler_options,
		       const struct btf *btf,
		       const struct bpf_prog_linfo *prog_linfo,
		       __u64 func_ksym, unsigned int func_idx,
		       bool linum)
{
}