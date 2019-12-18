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
typedef  int /*<<< orphan*/ * PWCHAR ;
typedef  int /*<<< orphan*/  PLDAPMessage ;
typedef  int /*<<< orphan*/  PLDAP ;
typedef  scalar_t__ PCWCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  kull_m_string_copy (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int ldap_count_values (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** ldap_get_values (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_value_free (int /*<<< orphan*/ **) ; 

PWCHAR kuhl_m_lsadump_dcshadow_getSingleTextAttr(PLDAP ld, PLDAPMessage pMessage, PCWCHAR attr)
{
	PWCHAR *tmp, result = NULL;
	if(tmp = ldap_get_values(ld, pMessage, (PWCHAR) attr))
	{
		if(ldap_count_values(tmp) == 1)
			kull_m_string_copy(&result, tmp[0]);
		ldap_value_free(tmp);
	}
	return result;
}