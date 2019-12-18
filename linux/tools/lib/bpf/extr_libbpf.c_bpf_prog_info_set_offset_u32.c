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
struct bpf_prog_info {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */

__attribute__((used)) static void bpf_prog_info_set_offset_u32(struct bpf_prog_info *info, int offset,
					 __u32 val)
{
	__u32 *array = (__u32 *)info;

	if (offset >= 0)
		array[offset / sizeof(__u32)] = val;
}