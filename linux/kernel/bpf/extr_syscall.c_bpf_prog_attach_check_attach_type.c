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
struct bpf_prog {int type; int expected_attach_type; int /*<<< orphan*/  enforce_expected_attach_type; } ;
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;

/* Variables and functions */
#define  BPF_PROG_TYPE_CGROUP_SKB 131 
#define  BPF_PROG_TYPE_CGROUP_SOCK 130 
#define  BPF_PROG_TYPE_CGROUP_SOCKOPT 129 
#define  BPF_PROG_TYPE_CGROUP_SOCK_ADDR 128 
 int EINVAL ; 

__attribute__((used)) static int bpf_prog_attach_check_attach_type(const struct bpf_prog *prog,
					     enum bpf_attach_type attach_type)
{
	switch (prog->type) {
	case BPF_PROG_TYPE_CGROUP_SOCK:
	case BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
	case BPF_PROG_TYPE_CGROUP_SOCKOPT:
		return attach_type == prog->expected_attach_type ? 0 : -EINVAL;
	case BPF_PROG_TYPE_CGROUP_SKB:
		return prog->enforce_expected_attach_type &&
			prog->expected_attach_type != attach_type ?
			-EINVAL : 0;
	default:
		return 0;
	}
}