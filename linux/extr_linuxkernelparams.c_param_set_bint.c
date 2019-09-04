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
struct kernel_param {int* arg; } ;

/* Variables and functions */
 int param_set_bool (char const*,struct kernel_param*) ; 

int param_set_bint(const char *val, const struct kernel_param *kp)
{
	/* Match bool exactly, by re-using it. */
	struct kernel_param boolkp = *kp;
	bool v;
	int ret;

	boolkp.arg = &v;

	ret = param_set_bool(val, &boolkp);
	if (ret == 0)
		*(int *)kp->arg = v;
	return ret;
}