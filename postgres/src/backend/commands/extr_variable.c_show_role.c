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

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentRoleId () ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 char const* role_string ; 

const char *
show_role(void)
{
	/*
	 * Check whether SET ROLE is active; if not return "none".  This is a
	 * kluge to deal with the fact that SET SESSION AUTHORIZATION logically
	 * resets SET ROLE to NONE, but we cannot set the GUC role variable from
	 * assign_session_authorization (because we haven't got enough info to
	 * call set_config_option).
	 */
	if (!OidIsValid(GetCurrentRoleId()))
		return "none";

	/* Otherwise we can just use the GUC string */
	return role_string ? role_string : "none";
}