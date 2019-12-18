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
struct TYPE_3__ {char* szDCDsServiceName; size_t dwDomainControllerFunctionality; void* szDsServiceName; void* szSchemaNamingContext; void* szConfigurationNamingContext; void* szDomainNamingContext; void* maxDCUsn; int /*<<< orphan*/  ld; } ;
typedef  char* PWCHAR ;
typedef  int /*<<< orphan*/ * PLDAPMessage ;
typedef  TYPE_1__* PDCSHADOW_DOMAIN_INFO ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARRAYSIZE (char**) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LDAP_SCOPE_BASE ; 
 scalar_t__ LDAP_SUCCESS ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 char** SZ_DOMAIN_CONTROLLER_FUNCTIONALITY ; 
 int /*<<< orphan*/  kprintf (char*,size_t,...) ; 
 void* kuhl_m_lsadump_dcshadow_getSingleTextAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ kull_m_string_copy (void**,char*) ; 
 int ldap_count_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 scalar_t__ ldap_search_s (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 char* wcsstr (char*,char*) ; 
 void* wcstoul (char*,int /*<<< orphan*/ *,int) ; 

BOOL kuhl_m_lsadump_dcshadow_domaininfo_rootDse(PDCSHADOW_DOMAIN_INFO info)
{
	DWORD dwErr;
	PWCHAR rootAttr[] = {L"rootDomainNamingContext", L"configurationNamingContext", L"schemaNamingContext", L"dsServiceName", L"domainControllerFunctionality", L"highestCommittedUSN", NULL};
	PLDAPMessage pMessage = NULL;
	PWCHAR tmp, p;
	
	dwErr = ldap_search_s(info->ld, NULL, LDAP_SCOPE_BASE, NULL, rootAttr, FALSE, &pMessage);
	if(dwErr == LDAP_SUCCESS)
	{
		if(ldap_count_entries(info->ld, pMessage) == 1)
		{
			if(info->szDomainNamingContext = kuhl_m_lsadump_dcshadow_getSingleTextAttr(info->ld, pMessage, rootAttr[0]))
				kprintf(L"Domain:         %s\n", info->szDomainNamingContext);
			if(info->szConfigurationNamingContext = kuhl_m_lsadump_dcshadow_getSingleTextAttr(info->ld, pMessage, rootAttr[1]))
				kprintf(L"Configuration:  %s\n", info->szConfigurationNamingContext);
			if(info->szSchemaNamingContext = kuhl_m_lsadump_dcshadow_getSingleTextAttr(info->ld, pMessage, rootAttr[2]))
				kprintf(L"Schema:         %s\n", info->szSchemaNamingContext);
			if(info->szDCDsServiceName = kuhl_m_lsadump_dcshadow_getSingleTextAttr(info->ld, pMessage, rootAttr[3]))
			{
				p = wcsstr(info->szDCDsServiceName, L",CN=");
				if(p)
				{
					p = wcsstr(p + 1, L",CN=");
					if(p && (p + 1) && kull_m_string_copy(&info->szDsServiceName, p));
						kprintf(L"dsServiceName:  %s\n", info->szDsServiceName);
				}
			}
			if(tmp = kuhl_m_lsadump_dcshadow_getSingleTextAttr(info->ld, pMessage, rootAttr[4]))
			{
				info->dwDomainControllerFunctionality = wcstoul(tmp, NULL, 10);
				LocalFree(tmp);
			}
			kprintf(L"domainControllerFunctionality: %u ( %s )\n", info->dwDomainControllerFunctionality, (info->dwDomainControllerFunctionality < ARRAYSIZE(SZ_DOMAIN_CONTROLLER_FUNCTIONALITY) ? SZ_DOMAIN_CONTROLLER_FUNCTIONALITY[info->dwDomainControllerFunctionality] : L"?"));
			if(tmp = kuhl_m_lsadump_dcshadow_getSingleTextAttr(info->ld, pMessage, rootAttr[5]))
			{
				info->maxDCUsn = wcstoul(tmp, NULL, 10);
				LocalFree(tmp);
			}
			kprintf(L"highestCommittedUSN: %u\n", info->maxDCUsn);
		}
		else PRINT_ERROR(L"ldap_count_entries is NOT 1\n");
		ldap_msgfree(pMessage);
	}
	else PRINT_ERROR(L"ldap_search_s 0x%x (%u)\n", dwErr, dwErr);	
	return (dwErr == LDAP_SUCCESS) && info->szDomainNamingContext && info->szConfigurationNamingContext && info->szSchemaNamingContext && info->szDsServiceName;
}