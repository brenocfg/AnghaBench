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
typedef  char* PWCHAR ;
typedef  int /*<<< orphan*/ * PLDAPMessage ;
typedef  int /*<<< orphan*/  PLDAP ;
typedef  int /*<<< orphan*/  PCWCHAR ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LDAP_SCOPE_SUBTREE ; 
 scalar_t__ LDAP_SUCCESS ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  kuhl_m_sid_displayMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* kuhl_m_sid_filterFromArgs (int,int /*<<< orphan*/ **) ; 
 scalar_t__ kull_m_ldap_getLdapAndRootDN (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int ldap_count_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 scalar_t__ ldap_search_s (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char**,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ldap_unbind (int /*<<< orphan*/ ) ; 

BOOL kuhl_m_sid_quickSearch(int argc, wchar_t * argv[], BOOL needUnique, PCWCHAR system, PLDAP *ld, PLDAPMessage *pMessage)
{
	BOOL status = FALSE;
	DWORD dwErr;
	PWCHAR myAttrs[] = {L"name", L"sAMAccountName", L"objectSid", L"sIDHistory", L"objectGUID", NULL}, dn, filter;
	if(filter = kuhl_m_sid_filterFromArgs(argc, argv))
	{
		if(kull_m_ldap_getLdapAndRootDN(system, NULL, ld, &dn))
		{
			*pMessage = NULL;
			dwErr = ldap_search_s(*ld, dn, LDAP_SCOPE_SUBTREE, filter, myAttrs, FALSE, pMessage);
			if(status = (dwErr == LDAP_SUCCESS))
			{
				switch(ldap_count_entries(*ld, *pMessage))
				{
				case 0:
					status = FALSE;
					PRINT_ERROR(L"No result! - filter was \'%s\'\n", filter);
					break;
				case 1:
					break;
				default:
					if(needUnique)
					{
						PRINT_ERROR(L"Not unique - Please: don\'t brick your AD! - filter was \'%s\'\n", filter);
						status = FALSE;
					}
					break;
				}
			}
			else PRINT_ERROR(L"ldap_search_s 0x%x (%u)\n", dwErr, dwErr);
			
			if(status)
				kuhl_m_sid_displayMessage(*ld, *pMessage);
			else
			{
				if(*pMessage)
					ldap_msgfree(*pMessage);
				ldap_unbind(*ld);
			}
			LocalFree(dn);
		}
		LocalFree(filter);
	}
	return status;
}