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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MSR_IA32_TEMPERATURE_TARGET ; 
 int rdmsr_safe (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int get_tj_max(u32 *tj_max)
{
	u32 eax, edx;
	u32 val;
	int err;

	err = rdmsr_safe(MSR_IA32_TEMPERATURE_TARGET, &eax, &edx);
	if (err)
		goto err_ret;
	else {
		val = (eax >> 16) & 0xff;
		if (val)
			*tj_max = val * 1000;
		else {
			err = -EINVAL;
			goto err_ret;
		}
	}

	return 0;
err_ret:
	*tj_max = 0;

	return err;
}