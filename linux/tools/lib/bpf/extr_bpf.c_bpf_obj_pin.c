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
union bpf_attr {int bpf_fd; int /*<<< orphan*/  pathname; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_OBJ_PIN ; 
 int /*<<< orphan*/  memset (union bpf_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptr_to_u64 (void*) ; 
 int sys_bpf (int /*<<< orphan*/ ,union bpf_attr*,int) ; 

int bpf_obj_pin(int fd, const char *pathname)
{
	union bpf_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.pathname = ptr_to_u64((void *)pathname);
	attr.bpf_fd = fd;

	return sys_bpf(BPF_OBJ_PIN, &attr, sizeof(attr));
}