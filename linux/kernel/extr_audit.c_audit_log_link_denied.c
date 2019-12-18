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
 int /*<<< orphan*/  AUDIT_ANOM_LINK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_context () ; 
 scalar_t__ audit_dummy_context () ; 
 int /*<<< orphan*/  audit_enabled ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_task_info (struct audit_buffer*) ; 

void audit_log_link_denied(const char *operation)
{
	struct audit_buffer *ab;

	if (!audit_enabled || audit_dummy_context())
		return;

	/* Generate AUDIT_ANOM_LINK with subject, operation, outcome. */
	ab = audit_log_start(audit_context(), GFP_KERNEL, AUDIT_ANOM_LINK);
	if (!ab)
		return;
	audit_log_format(ab, "op=%s", operation);
	audit_log_task_info(ab);
	audit_log_format(ab, " res=0");
	audit_log_end(ab);
}