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
 int /*<<< orphan*/  prev_row_security_policy_hook_permissive ; 
 int /*<<< orphan*/  prev_row_security_policy_hook_restrictive ; 
 int /*<<< orphan*/  row_security_policy_hook_permissive ; 
 int /*<<< orphan*/  row_security_policy_hook_restrictive ; 
 int /*<<< orphan*/  test_rls_hooks_permissive ; 
 int /*<<< orphan*/  test_rls_hooks_restrictive ; 

void
_PG_init(void)
{
	/* Save values for unload  */
	prev_row_security_policy_hook_permissive = row_security_policy_hook_permissive;
	prev_row_security_policy_hook_restrictive = row_security_policy_hook_restrictive;

	/* Set our hooks */
	row_security_policy_hook_permissive = test_rls_hooks_permissive;
	row_security_policy_hook_restrictive = test_rls_hooks_restrictive;
}