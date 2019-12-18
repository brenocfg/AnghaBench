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

/* Variables and functions */
 int /*<<< orphan*/  debug_printf (char*,int,...) ; 
 int isst_send_msr_command (int,int,int /*<<< orphan*/ ,unsigned long long*) ; 

int isst_get_trl_bucket_info(int cpu, unsigned long long *buckets_info)
{
	int ret;

	debug_printf("cpu:%d bucket info via MSR\n", cpu);

	*buckets_info = 0;

	ret = isst_send_msr_command(cpu, 0x1ae, 0, buckets_info);
	if (ret)
		return ret;

	debug_printf("cpu:%d bucket info via MSR successful 0x%llx\n", cpu,
		     *buckets_info);

	return 0;
}