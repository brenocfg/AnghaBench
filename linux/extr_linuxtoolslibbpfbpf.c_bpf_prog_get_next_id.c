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
union bpf_attr {int /*<<< orphan*/  next_id; int /*<<< orphan*/  start_id; } ;
typedef  int /*<<< orphan*/  attr ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_GET_NEXT_ID ; 
 int /*<<< orphan*/  bzero (union bpf_attr*,int) ; 
 int sys_bpf (int /*<<< orphan*/ ,union bpf_attr*,int) ; 

int bpf_prog_get_next_id(__u32 start_id, __u32 *next_id)
{
	union bpf_attr attr;
	int err;

	bzero(&attr, sizeof(attr));
	attr.start_id = start_id;

	err = sys_bpf(BPF_PROG_GET_NEXT_ID, &attr, sizeof(attr));
	if (!err)
		*next_id = attr.next_id;

	return err;
}