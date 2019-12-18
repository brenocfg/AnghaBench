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
 int /*<<< orphan*/  memset (union bpf_attr*,int /*<<< orphan*/ ,int) ; 
 int sys_bpf (int,union bpf_attr*,int) ; 

__attribute__((used)) static int bpf_obj_get_next_id(__u32 start_id, __u32 *next_id, int cmd)
{
	union bpf_attr attr;
	int err;

	memset(&attr, 0, sizeof(attr));
	attr.start_id = start_id;

	err = sys_bpf(cmd, &attr, sizeof(attr));
	if (!err)
		*next_id = attr.next_id;

	return err;
}