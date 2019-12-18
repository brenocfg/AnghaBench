#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int prog_fd; int /*<<< orphan*/  name; } ;
union bpf_attr {TYPE_1__ raw_tracepoint; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_RAW_TRACEPOINT_OPEN ; 
 int /*<<< orphan*/  memset (union bpf_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptr_to_u64 (char const*) ; 
 int sys_bpf (int /*<<< orphan*/ ,union bpf_attr*,int) ; 

int bpf_raw_tracepoint_open(const char *name, int prog_fd)
{
	union bpf_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.raw_tracepoint.name = ptr_to_u64(name);
	attr.raw_tracepoint.prog_fd = prog_fd;

	return sys_bpf(BPF_RAW_TRACEPOINT_OPEN, &attr, sizeof(attr));
}