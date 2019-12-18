#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct audit_krule {int /*<<< orphan*/  listnr; int /*<<< orphan*/  filterkey; TYPE_1__* tree; } ;
struct audit_context {int dummy; } ;
struct audit_buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pathname; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_CONFIG_CHANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_enabled ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 int /*<<< orphan*/  audit_log_key (struct audit_buffer*,int /*<<< orphan*/ ) ; 
 struct audit_buffer* audit_log_start (struct audit_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_untrustedstring (struct audit_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void audit_tree_log_remove_rule(struct audit_context *context,
				       struct audit_krule *rule)
{
	struct audit_buffer *ab;

	if (!audit_enabled)
		return;
	ab = audit_log_start(context, GFP_KERNEL, AUDIT_CONFIG_CHANGE);
	if (unlikely(!ab))
		return;
	audit_log_format(ab, "op=remove_rule dir=");
	audit_log_untrustedstring(ab, rule->tree->pathname);
	audit_log_key(ab, rule->filterkey);
	audit_log_format(ab, " list=%d res=1", rule->listnr);
	audit_log_end(ab);
}