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
struct TYPE_3__ {char* szConfigurationNamingContext; int /*<<< orphan*/  ld; int /*<<< orphan*/  szDCDsServiceName; int /*<<< orphan*/  szDCFQDN; } ;
typedef  char* PWSTR ;
typedef  int /*<<< orphan*/ * PLDAPMessage ;
typedef  TYPE_1__* PDCSHADOW_DOMAIN_INFO ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  LDAP ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LDAP_SCOPE_BASE ; 
 int /*<<< orphan*/  LDAP_SCOPE_SUBTREE ; 
 scalar_t__ LDAP_SUCCESS ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__,scalar_t__,...) ; 
 scalar_t__ _wcsicmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 
 char* kuhl_m_lsadump_dcshadow_getSingleTextAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ kuhl_m_lsadump_dcshadow_init_ldap (char*,int /*<<< orphan*/ **) ; 
 scalar_t__ kuhl_m_lsadump_dcshadow_lingering_trigger (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* ldap_get_dn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldap_next_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ldap_search_s (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ldap_unbind (int /*<<< orphan*/ *) ; 
 char* wcsstr (char*,char*) ; 

NTSTATUS kuhl_m_lsadump_dcshadow_lingering_propagate(PDCSHADOW_DOMAIN_INFO info, PWSTR szObjectToKill)
{
	DWORD dwErr;
	PLDAPMessage pMessage = NULL, pEntry, pServerMessage;
	PWSTR szNTDSADn;
	PWSTR szServerDN, szServerFQDN;
	LDAP* ld;
	PWSTR szAttributes[] = {L"dNSHostName", NULL};
	dwErr = ldap_search_s(info->ld, info->szConfigurationNamingContext, LDAP_SCOPE_SUBTREE, L"(objectClass=nTDSDSA)", NULL, FALSE, &pMessage);
	if(dwErr == LDAP_SUCCESS)
	{
		pEntry = pMessage;
		while(pEntry != NULL)
		{
			szNTDSADn = ldap_get_dn(info->ld, pEntry);
			szServerDN = wcsstr(szNTDSADn, L",CN=") + 1;
			dwErr = ldap_search_s(info->ld, szServerDN, LDAP_SCOPE_BASE, NULL, szAttributes, FALSE, &pServerMessage);
			if(dwErr == LDAP_SUCCESS)
			{
				szServerFQDN = kuhl_m_lsadump_dcshadow_getSingleTextAttr(info->ld, pServerMessage, szAttributes[0]);
				if (szServerFQDN && _wcsicmp(szServerFQDN, info->szDCFQDN) != 0)
				{
					kprintf(L"  * %s\n", szServerFQDN);
					if (!(dwErr = kuhl_m_lsadump_dcshadow_init_ldap(szServerFQDN, &ld)))
					{
						dwErr = kuhl_m_lsadump_dcshadow_lingering_trigger(ld, info->szDCDsServiceName, szObjectToKill);
						if (dwErr)
							PRINT_ERROR(L"trigger lingering for %s 0x%x (%u)\n", szServerFQDN, dwErr, dwErr);
						ldap_unbind(ld);
					}
					else PRINT_ERROR(L"ldap_connect 0x%x (%u)\n", dwErr, dwErr);
					LocalFree(szServerFQDN);
				}
				ldap_msgfree(pServerMessage);
			}

			pEntry = ldap_next_entry(info->ld, pEntry);
		}
		ldap_msgfree(pMessage);
	}
	return dwErr;
}