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
struct TYPE_3__ {scalar_t__ szFakeDN; scalar_t__ szFakeFQDN; int /*<<< orphan*/  ld; int /*<<< orphan*/  szDomainNamingContext; int /*<<< orphan*/  szFakeDCNetBIOS; } ;
typedef  char* PWSTR ;
typedef  TYPE_1__* PDCSHADOW_DOMAIN_INFO ;
typedef  int /*<<< orphan*/  LDAPMessage ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LDAP_SCOPE_SUBTREE ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kuhl_m_lsadump_dcshadow_getSingleTextAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kull_m_string_copy (scalar_t__*,char*) ; 
 scalar_t__ kull_m_string_sprintf (char**,char*,int /*<<< orphan*/ ) ; 
 char* ldap_get_dn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_memfree (char*) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_search_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

BOOL kuhl_m_lsadump_dcshadow_domaininfo_computer(PDCSHADOW_DOMAIN_INFO info)
{
	DWORD dwErr;
	PWSTR szComputerFilter, szTempComputerDN;
	PWSTR szComputerAttributes[] = {L"distinguishedName",L"userAccountControl", L"dNSHostName", NULL};
	LDAPMessage *pComputerSearchResult = NULL;

	if(kull_m_string_sprintf(&szComputerFilter, L"(&(|(objectClass=user)(objectClass=computer))(sAMAccountName=%s$))", info->szFakeDCNetBIOS))
	{
		// search for computer info in LDAP
		if(!(dwErr = ldap_search_s(info->ld, info->szDomainNamingContext, LDAP_SCOPE_SUBTREE, szComputerFilter, szComputerAttributes, FALSE, &pComputerSearchResult)))
		{
			szTempComputerDN = ldap_get_dn(info->ld,pComputerSearchResult);
			kull_m_string_copy(&info->szFakeDN, szTempComputerDN);
			ldap_memfree(szTempComputerDN);
			info->szFakeFQDN  = kuhl_m_lsadump_dcshadow_getSingleTextAttr(info->ld, pComputerSearchResult, L"dNSHostName");
			ldap_msgfree(pComputerSearchResult);
		}
		else PRINT_ERROR(L"computer not found in AD 0x%x (%u)\n", dwErr, dwErr);
	}
	return info->szFakeFQDN && info->szFakeDN;
}