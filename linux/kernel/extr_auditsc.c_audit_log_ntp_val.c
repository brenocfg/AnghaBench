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
struct audit_ntp_val {scalar_t__ newval; scalar_t__ oldval; } ;
struct audit_ntp_data {struct audit_ntp_val* vals; } ;
typedef  enum audit_ntp_type { ____Placeholder_audit_ntp_type } audit_ntp_type ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_TIME_ADJNTPVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_context () ; 
 int /*<<< orphan*/  audit_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void audit_log_ntp_val(const struct audit_ntp_data *ad,
			      const char *op, enum audit_ntp_type type)
{
	const struct audit_ntp_val *val = &ad->vals[type];

	if (val->newval == val->oldval)
		return;

	audit_log(audit_context(), GFP_KERNEL, AUDIT_TIME_ADJNTPVAL,
		  "op=%s old=%lli new=%lli", op, val->oldval, val->newval);
}