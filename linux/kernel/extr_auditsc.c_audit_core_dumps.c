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
 int /*<<< orphan*/  AUDIT_ANOM_ABEND ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 long SIGQUIT ; 
 int /*<<< orphan*/  audit_context () ; 
 int /*<<< orphan*/  audit_enabled ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,long) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_task (struct audit_buffer*) ; 
 scalar_t__ unlikely (int) ; 

void audit_core_dumps(long signr)
{
	struct audit_buffer *ab;

	if (!audit_enabled)
		return;

	if (signr == SIGQUIT)	/* don't care for those */
		return;

	ab = audit_log_start(audit_context(), GFP_KERNEL, AUDIT_ANOM_ABEND);
	if (unlikely(!ab))
		return;
	audit_log_task(ab);
	audit_log_format(ab, " sig=%ld res=1", signr);
	audit_log_end(ab);
}