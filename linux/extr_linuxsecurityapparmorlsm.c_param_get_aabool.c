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
 int param_get_bool (char*,struct kernel_param const*) ; 
 int /*<<< orphan*/  policy_view_capable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int param_get_aabool(char *buffer, const struct kernel_param *kp)
{
	if (!apparmor_enabled)
		return -EINVAL;
	if (apparmor_initialized && !policy_view_capable(NULL))
		return -EPERM;
	return param_get_bool(buffer, kp);
}