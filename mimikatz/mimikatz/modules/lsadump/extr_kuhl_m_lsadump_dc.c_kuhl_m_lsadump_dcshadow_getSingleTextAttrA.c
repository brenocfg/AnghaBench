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
typedef  int /*<<< orphan*/ * PSTR ;
typedef  int /*<<< orphan*/  PLDAPMessage ;
typedef  int /*<<< orphan*/  PLDAP ;
typedef  scalar_t__ PCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  kull_m_string_copyA (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int ldap_count_valuesA (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** ldap_get_valuesA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_value_freeA (int /*<<< orphan*/ **) ; 

PSTR kuhl_m_lsadump_dcshadow_getSingleTextAttrA(PLDAP ld, PLDAPMessage pMessage, PCSTR attr)
{
	PSTR *tmp, result = NULL;
	
	if(tmp = ldap_get_valuesA(ld, pMessage, (PSTR) attr))
	{
		if(ldap_count_valuesA(tmp) == 1)
			kull_m_string_copyA(&result, tmp[0]);
		ldap_value_freeA(tmp);
	}
	return result;
}