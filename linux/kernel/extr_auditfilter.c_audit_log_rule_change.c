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
struct audit_krule {int /*<<< orphan*/  listnr; int /*<<< orphan*/  filterkey; } ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_CONFIG_CHANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_context () ; 
 int /*<<< orphan*/  audit_enabled ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,char*,...) ; 
 int /*<<< orphan*/  audit_log_key (struct audit_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_session_info (struct audit_buffer*) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_task_context (struct audit_buffer*) ; 

__attribute__((used)) static void audit_log_rule_change(char *action, struct audit_krule *rule, int res)
{
	struct audit_buffer *ab;

	if (!audit_enabled)
		return;

	ab = audit_log_start(audit_context(), GFP_KERNEL, AUDIT_CONFIG_CHANGE);
	if (!ab)
		return;
	audit_log_session_info(ab);
	audit_log_task_context(ab);
	audit_log_format(ab, " op=%s", action);
	audit_log_key(ab, rule->filterkey);
	audit_log_format(ab, " list=%d res=%d", rule->listnr, res);
	audit_log_end(ab);
}