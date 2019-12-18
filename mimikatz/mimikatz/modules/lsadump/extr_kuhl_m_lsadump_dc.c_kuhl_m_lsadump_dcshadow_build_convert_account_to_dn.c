#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  szObjectDN; } ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/ * PLDAPMessage ;
typedef  int /*<<< orphan*/  PLDAP ;
typedef  TYPE_1__* PDCSHADOW_PUSH_REQUEST_OBJECT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LDAP_SCOPE_SUBTREE ; 
 scalar_t__ LDAP_SUCCESS ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ kull_m_string_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_string_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldap_get_dnW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 scalar_t__ ldap_search_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

BOOL kuhl_m_lsadump_dcshadow_build_convert_account_to_dn(PLDAP ld, PWSTR szDomainNamingContext, PDCSHADOW_PUSH_REQUEST_OBJECT object)
{
	BOOL status = FALSE; 
	DWORD dwErr;
	PLDAPMessage pMessage = NULL;
	PWSTR szFilter, szDN;
	
	if(kull_m_string_sprintf(&szFilter, L"(sAMAccountName=%s)", object->szObjectDN))
	{
		dwErr = ldap_search_s(ld, szDomainNamingContext, LDAP_SCOPE_SUBTREE, szFilter, NULL, FALSE, &pMessage);
		if(dwErr == LDAP_SUCCESS)
		{
			if(szDN = ldap_get_dnW(ld, pMessage))
			{
				LocalFree(object->szObjectDN);
				if(kull_m_string_copy(&object->szObjectDN, szDN))
					status = TRUE;
			}
			ldap_msgfree(pMessage);
		}
		LocalFree(szFilter);
	}
	return status;
}