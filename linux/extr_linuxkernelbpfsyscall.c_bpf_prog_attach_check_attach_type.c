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
struct bpf_prog {int type; int expected_attach_type; } ;
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;

/* Variables and functions */
#define  BPF_PROG_TYPE_CGROUP_SOCK 129 
#define  BPF_PROG_TYPE_CGROUP_SOCK_ADDR 128 
 int EINVAL ; 

__attribute__((used)) static int bpf_prog_attach_check_attach_type(const struct bpf_prog *prog,
					     enum bpf_attach_type attach_type)
{
	switch (prog->type) {
	case BPF_PROG_TYPE_CGROUP_SOCK:
	case BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
		return attach_type == prog->expected_attach_type ? 0 : -EINVAL;
	default:
		return 0;
	}
}