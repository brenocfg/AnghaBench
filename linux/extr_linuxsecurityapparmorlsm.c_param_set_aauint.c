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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  aa_g_path_max ; 
 int /*<<< orphan*/  apparmor_enabled ; 
 scalar_t__ apparmor_initialized ; 
 int param_set_uint (char const*,struct kernel_param const*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int param_set_aauint(const char *val, const struct kernel_param *kp)
{
	int error;

	if (!apparmor_enabled)
		return -EINVAL;
	/* file is ro but enforce 2nd line check */
	if (apparmor_initialized)
		return -EPERM;

	error = param_set_uint(val, kp);
	pr_info("AppArmor: buffer size set to %d bytes\n", aa_g_path_max);

	return error;
}