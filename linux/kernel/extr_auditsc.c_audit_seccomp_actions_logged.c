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
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_CONFIG_CHANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_context () ; 
 int /*<<< orphan*/  audit_enabled ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,char const*,char const*,int) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void audit_seccomp_actions_logged(const char *names, const char *old_names,
				  int res)
{
	struct audit_buffer *ab;

	if (!audit_enabled)
		return;

	ab = audit_log_start(audit_context(), GFP_KERNEL,
			     AUDIT_CONFIG_CHANGE);
	if (unlikely(!ab))
		return;

	audit_log_format(ab,
			 "op=seccomp-logging actions=%s old-actions=%s res=%d",
			 names, old_names, res);
	audit_log_end(ab);
}