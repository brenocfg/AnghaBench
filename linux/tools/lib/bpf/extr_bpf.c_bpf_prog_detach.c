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
union bpf_attr {int target_fd; int attach_type; } ;
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_DETACH ; 
 int /*<<< orphan*/  memset (union bpf_attr*,int /*<<< orphan*/ ,int) ; 
 int sys_bpf (int /*<<< orphan*/ ,union bpf_attr*,int) ; 

int bpf_prog_detach(int target_fd, enum bpf_attach_type type)
{
	union bpf_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.target_fd	 = target_fd;
	attr.attach_type = type;

	return sys_bpf(BPF_PROG_DETACH, &attr, sizeof(attr));
}