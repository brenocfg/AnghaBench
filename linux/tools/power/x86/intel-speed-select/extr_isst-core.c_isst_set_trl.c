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
 int isst_send_msr_command (int,int,int,unsigned long long*) ; 

int isst_set_trl(int cpu, unsigned long long trl)
{
	int ret;

	if (!trl)
		trl = 0xFFFFFFFFFFFFFFFFULL;

	ret = isst_send_msr_command(cpu, 0x1AD, 1, &trl);
	if (ret)
		return ret;

	return 0;
}