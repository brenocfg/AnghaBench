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

/* Variables and functions */
 scalar_t__ AUDIT_LOCKED ; 
 scalar_t__ AUDIT_OFF ; 
 int EPERM ; 
 scalar_t__ audit_enabled ; 
 int audit_log_config_change (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int audit_do_config_change(char *function_name, u32 *to_change, u32 new)
{
	int allow_changes, rc = 0;
	u32 old = *to_change;

	/* check if we are locked */
	if (audit_enabled == AUDIT_LOCKED)
		allow_changes = 0;
	else
		allow_changes = 1;

	if (audit_enabled != AUDIT_OFF) {
		rc = audit_log_config_change(function_name, new, old, allow_changes);
		if (rc)
			allow_changes = 0;
	}

	/* If we are allowed, make the change */
	if (allow_changes == 1)
		*to_change = new;
	/* Not allowed, update reason */
	else if (rc == 0)
		rc = -EPERM;
	return rc;
}