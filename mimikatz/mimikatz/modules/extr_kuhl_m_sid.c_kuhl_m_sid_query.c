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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/ * PLDAPMessage ;
typedef  int /*<<< orphan*/  PLDAP ;
typedef  int /*<<< orphan*/ * PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ kuhl_m_sid_quickSearch (int,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_unbind (int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_sid_query(int argc, wchar_t * argv[])
{
	PLDAP ld;
	PLDAPMessage pMessage = NULL;
	PCWCHAR szSystem = NULL;
	kull_m_string_args_byName(argc, argv, L"system", &szSystem, NULL);

	if(kuhl_m_sid_quickSearch(argc, argv, FALSE, szSystem, &ld, &pMessage))
	{
		if(pMessage)
			ldap_msgfree(pMessage);
		ldap_unbind(ld);
	}
	return STATUS_SUCCESS;
}