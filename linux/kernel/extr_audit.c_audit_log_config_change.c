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
typedef  int /*<<< orphan*/  u32 ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_CONFIG_CHANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_context () ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 int /*<<< orphan*/  audit_log_session_info (struct audit_buffer*) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int audit_log_task_context (struct audit_buffer*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int audit_log_config_change(char *function_name, u32 new, u32 old,
				   int allow_changes)
{
	struct audit_buffer *ab;
	int rc = 0;

	ab = audit_log_start(audit_context(), GFP_KERNEL, AUDIT_CONFIG_CHANGE);
	if (unlikely(!ab))
		return rc;
	audit_log_format(ab, "op=set %s=%u old=%u ", function_name, new, old);
	audit_log_session_info(ab);
	rc = audit_log_task_context(ab);
	if (rc)
		allow_changes = 0; /* Something weird, deny request */
	audit_log_format(ab, " res=%d", allow_changes);
	audit_log_end(ab);
	return rc;
}