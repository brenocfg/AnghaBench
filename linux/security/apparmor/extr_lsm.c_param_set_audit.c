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
 int /*<<< orphan*/  AUDIT_MAX_INDEX ; 
 int EINVAL ; 
 int EPERM ; 
 int aa_g_audit ; 
 int /*<<< orphan*/  apparmor_enabled ; 
 scalar_t__ apparmor_initialized ; 
 int /*<<< orphan*/  audit_mode_names ; 
 int match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  policy_admin_capable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int param_set_audit(const char *val, const struct kernel_param *kp)
{
	int i;

	if (!apparmor_enabled)
		return -EINVAL;
	if (!val)
		return -EINVAL;
	if (apparmor_initialized && !policy_admin_capable(NULL))
		return -EPERM;

	i = match_string(audit_mode_names, AUDIT_MAX_INDEX, val);
	if (i < 0)
		return -EINVAL;

	aa_g_audit = i;
	return 0;
}