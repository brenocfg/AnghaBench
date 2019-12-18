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
struct TYPE_2__ {int target_fd; int attach_type; void* prog_cnt; void* attach_flags; int /*<<< orphan*/  prog_ids; void* query_flags; } ;
union bpf_attr {TYPE_1__ query; } ;
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;
typedef  int /*<<< orphan*/  attr ;
typedef  void* __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_QUERY ; 
 int /*<<< orphan*/  memset (union bpf_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptr_to_u64 (void**) ; 
 int sys_bpf (int /*<<< orphan*/ ,union bpf_attr*,int) ; 

int bpf_prog_query(int target_fd, enum bpf_attach_type type, __u32 query_flags,
		   __u32 *attach_flags, __u32 *prog_ids, __u32 *prog_cnt)
{
	union bpf_attr attr;
	int ret;

	memset(&attr, 0, sizeof(attr));
	attr.query.target_fd	= target_fd;
	attr.query.attach_type	= type;
	attr.query.query_flags	= query_flags;
	attr.query.prog_cnt	= *prog_cnt;
	attr.query.prog_ids	= ptr_to_u64(prog_ids);

	ret = sys_bpf(BPF_PROG_QUERY, &attr, sizeof(attr));
	if (attach_flags)
		*attach_flags = attr.query.attach_flags;
	*prog_cnt = attr.query.prog_cnt;
	return ret;
}