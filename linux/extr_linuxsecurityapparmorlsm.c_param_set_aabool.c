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
 int /*<<< orphan*/  apparmor_enabled ; 
 scalar_t__ apparmor_initialized ; 
 int param_set_bool (char const*,struct kernel_param const*) ; 
 int /*<<< orphan*/  policy_admin_capable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int param_set_aabool(const char *val, const struct kernel_param *kp)
{
	if (!apparmor_enabled)
		return -EINVAL;
	if (apparmor_initialized && !policy_admin_capable(NULL))
		return -EPERM;
	return param_set_bool(val, kp);
}