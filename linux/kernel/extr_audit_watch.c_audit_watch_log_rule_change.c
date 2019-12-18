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
struct audit_watch {int /*<<< orphan*/  path; } ;
struct audit_krule {char* listnr; int /*<<< orphan*/  filterkey; } ;
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

__attribute__((used)) static void audit_watch_log_rule_change(struct audit_krule *r, struct audit_watch *w, char *op)
{
	struct audit_buffer *ab;

	if (!audit_enabled)
		return;
	ab = audit_log_start(audit_context(), GFP_NOFS, AUDIT_CONFIG_CHANGE);
	if (!ab)
		return;
	audit_log_session_info(ab);
	audit_log_format(ab, "op=%s path=", op);
	audit_log_untrustedstring(ab, w->path);
	audit_log_key(ab, r->filterkey);
	audit_log_format(ab, " list=%d res=1", r->listnr);
	audit_log_end(ab);
}