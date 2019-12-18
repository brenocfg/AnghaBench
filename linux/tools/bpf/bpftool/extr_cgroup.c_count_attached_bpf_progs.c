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
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;
typedef  int __u32 ;

/* Variables and functions */
 int bpf_prog_query (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  query_flags ; 

__attribute__((used)) static int count_attached_bpf_progs(int cgroup_fd, enum bpf_attach_type type)
{
	__u32 prog_cnt = 0;
	int ret;

	ret = bpf_prog_query(cgroup_fd, type, query_flags, NULL,
			     NULL, &prog_cnt);
	if (ret)
		return -1;

	return prog_cnt;
}