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
typedef  int /*<<< orphan*/  kp_local ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct kernel_param*,struct kernel_param const*,int) ; 
 int param_get_bool (char*,struct kernel_param*) ; 

__attribute__((used)) static int param_get_aaintbool(char *buffer, const struct kernel_param *kp)
{
	struct kernel_param kp_local;
	bool value;

	/* Create local copy, with arg pointing to bool type. */
	value = !!*((int *)kp->arg);
	memcpy(&kp_local, kp, sizeof(kp_local));
	kp_local.arg = &value;

	return param_get_bool(buffer, &kp_local);
}