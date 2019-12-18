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
struct berval {int bv_len; int /*<<< orphan*/  bv_val; } ;
struct TYPE_3__ {int* pbSchemaSignature; int /*<<< orphan*/  ld; int /*<<< orphan*/  szSchemaNamingContext; } ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/ * PLDAPMessage ;
typedef  TYPE_1__* PDCSHADOW_DOMAIN_INFO ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LDAP_SCOPE_BASE ; 
 scalar_t__ LDAP_SUCCESS ; 
 int /*<<< orphan*/  RtlCopyMemory (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (int*,int) ; 
 int /*<<< orphan*/ * TEXT (char*) ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int*,int,int /*<<< orphan*/ ) ; 
 struct berval** ldap_get_values_len (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 scalar_t__ ldap_search_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

BOOL kuhl_m_lsadump_dcshadow_domaininfo_schemasignature(PDCSHADOW_DOMAIN_INFO info)
{
	DWORD dwErr;
	PWSTR szAttributes[] = {TEXT("schemaInfo"), NULL};
	PLDAPMessage pMessage = NULL;
	struct berval** berSchemaInfo = NULL;
	
	dwErr = ldap_search_s(info->ld, info->szSchemaNamingContext, LDAP_SCOPE_BASE, NULL, szAttributes, FALSE, &pMessage);
	if(dwErr == LDAP_SUCCESS)
	{
		berSchemaInfo = ldap_get_values_len(info->ld, pMessage,szAttributes[0]);
		if(!berSchemaInfo || (*berSchemaInfo)->bv_len != 21)
		{
			// default signature
			info->pbSchemaSignature[0] = 0xFF;
			RtlZeroMemory(info->pbSchemaSignature + 1, 20);
		}
		else
			RtlCopyMemory(info->pbSchemaSignature, (*berSchemaInfo)->bv_val, 21);
		ldap_msgfree(pMessage);
		kprintf(L"schema signature:");
		kull_m_string_wprintf_hex(info->pbSchemaSignature, 21, 0);
		kprintf(L"\n");
	}
	return (dwErr == LDAP_SUCCESS);
}