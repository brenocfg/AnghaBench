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
struct audit_krule {char* listnr; int /*<<< orphan*/  filterkey; } ;
struct audit_fsnotify_mark {int /*<<< orphan*/  path; struct audit_krule* rule; } ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_CONFIG_CHANGE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  audit_context () ; 
 int /*<<< orphan*/  audit_enabled ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,char*) ; 
 int /*<<< orphan*/  audit_log_key (struct audit_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_session_info (struct audit_buffer*) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_untrustedstring (struct audit_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void audit_mark_log_rule_change(struct audit_fsnotify_mark *audit_mark, char *op)
{
	struct audit_buffer *ab;
	struct audit_krule *rule = audit_mark->rule;

	if (!audit_enabled)
		return;
	ab = audit_log_start(audit_context(), GFP_NOFS, AUDIT_CONFIG_CHANGE);
	if (unlikely(!ab))
		return;
	audit_log_session_info(ab);
	audit_log_format(ab, " op=%s path=", op);
	audit_log_untrustedstring(ab, audit_mark->path);
	audit_log_key(ab, rule->filterkey);
	audit_log_format(ab, " list=%d res=1", rule->listnr);
	audit_log_end(ab);
}