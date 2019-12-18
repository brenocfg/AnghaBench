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
struct TYPE_8__ {int /*<<< orphan*/  ld; int /*<<< orphan*/  szSchemaNamingContext; } ;
struct TYPE_6__ {size_t valCount; } ;
struct TYPE_7__ {char** pszValue; TYPE_1__ AttrVal; } ;
typedef  char* PWSTR ;
typedef  TYPE_2__* PDCSHADOW_PUSH_REQUEST_OBJECT_ATTRIBUTE ;
typedef  TYPE_3__* PDCSHADOW_DOMAIN_INFO ;
typedef  int /*<<< orphan*/  LDAPMessage ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LDAP_SCOPE_ONELEVEL ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 char* kuhl_m_lsadump_dcshadow_getSingleTextAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ kull_m_string_sprintf (char**,char*,char*) ; 
 int ldap_count_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 size_t ldap_search_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

BOOL kuhl_m_lsadump_dcshadow_build_replication_get_schema_oid_values(PDCSHADOW_DOMAIN_INFO info, PDCSHADOW_PUSH_REQUEST_OBJECT_ATTRIBUTE attr)
{
	BOOL fSuccess = FALSE;
	DWORD i, dwErr;
	PWSTR szFilter, szTempValue, szAttributes[] = {L"governsID", NULL};
	LDAPMessage *pSearchResult = NULL;
	
	for(i = 0; i< attr->AttrVal.valCount; i++)
	{	
		fSuccess = FALSE;
		if(kull_m_string_sprintf(&szFilter, L"(&(objectClass=classSchema)(lDAPDisplayName=%s))", attr->pszValue[i]))
		{
			if(!(dwErr = ldap_search_s(info->ld, info->szSchemaNamingContext, LDAP_SCOPE_ONELEVEL, szFilter, szAttributes, FALSE, &pSearchResult)))
			{
				if(ldap_count_entries(info->ld, pSearchResult) == 1)
				{
					szTempValue = kuhl_m_lsadump_dcshadow_getSingleTextAttr(info->ld, pSearchResult, szAttributes[0]);
					if(szTempValue)
					{
						LocalFree(attr->pszValue[i]);
						attr->pszValue[i]  = szTempValue;
						fSuccess = TRUE;
					}
				}
				else PRINT_ERROR(L"objectClass %s not found in AD\n", attr->pszValue[i]);
				ldap_msgfree(pSearchResult);
			}
			else PRINT_ERROR(L"objectClass not found in AD 0x%x (%u)\n", dwErr, dwErr);
		}
		if (!fSuccess)
			break;
	}
	return fSuccess;
}