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
struct bpf_prog {int dummy; } ;
struct bpf_insn_access_aux {int dummy; } ;
typedef  enum bpf_access_type { ____Placeholder_bpf_access_type } bpf_access_type ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int BPF_READ ; 

__attribute__((used)) static bool raw_tp_prog_is_valid_access(int off, int size,
					enum bpf_access_type type,
					const struct bpf_prog *prog,
					struct bpf_insn_access_aux *info)
{
	/* largest tracepoint in the kernel has 12 args */
	if (off < 0 || off >= sizeof(__u64) * 12)
		return false;
	if (type != BPF_READ)
		return false;
	if (off % size != 0)
		return false;
	return true;
}