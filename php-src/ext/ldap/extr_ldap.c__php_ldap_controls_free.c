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
typedef  int /*<<< orphan*/  LDAPControl ;

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ldap_control_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _php_ldap_controls_free (LDAPControl*** ctrls)
{
	LDAPControl **ctrlp;

	if (*ctrls) {
		ctrlp = *ctrls;
		while (*ctrlp) {
			ldap_control_free(*ctrlp);
			ctrlp++;
		}
		efree(*ctrls);
		*ctrls = NULL;
	}
}