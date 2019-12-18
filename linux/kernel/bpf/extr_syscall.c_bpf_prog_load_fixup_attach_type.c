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
union bpf_attr {int prog_type; int /*<<< orphan*/  expected_attach_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_CGROUP_INET_SOCK_CREATE ; 
#define  BPF_PROG_TYPE_CGROUP_SOCK 128 

__attribute__((used)) static void bpf_prog_load_fixup_attach_type(union bpf_attr *attr)
{
	switch (attr->prog_type) {
	case BPF_PROG_TYPE_CGROUP_SOCK:
		/* Unfortunately BPF_ATTACH_TYPE_UNSPEC enumeration doesn't
		 * exist so checking for non-zero is the way to go here.
		 */
		if (!attr->expected_attach_type)
			attr->expected_attach_type =
				BPF_CGROUP_INET_SOCK_CREATE;
		break;
	}
}