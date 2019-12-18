#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int length; int* value; } ;
struct TYPE_8__ {int /*<<< orphan*/  ld; int /*<<< orphan*/  szConfigurationNamingContext; } ;
struct TYPE_7__ {int dwSyntax; int /*<<< orphan*/  Oid; int /*<<< orphan*/  szAttributeName; } ;
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  char* PSTR ;
typedef  int /*<<< orphan*/ * PLDAPMessage ;
typedef  TYPE_1__* PDCSHADOW_OBJECT_ATTRIBUTE ;
typedef  TYPE_2__* PDCSHADOW_DOMAIN_INFO ;
typedef  TYPE_3__ OssEncodedOID ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LDAP_SCOPE_SUBTREE ; 
 int LDAP_SUCCESS ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_dcshadow_getSingleTextAttrA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ kull_m_asn1_DotVal2Eoid (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  kull_m_asn1_freeEnc (int*) ; 
 scalar_t__ kull_m_string_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int ldap_count_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char** ldap_get_valuesA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 int ldap_search_sW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ldap_value_freeA (char**) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int) ; 

BOOL kuhl_m_lsadump_dcshadow_build_replication_attribute(PDCSHADOW_DOMAIN_INFO info, PDCSHADOW_OBJECT_ATTRIBUTE attribute)
{
	DWORD dwErr;
	PWCHAR attributesFilter;
	PLDAPMessage pAttributeMessage = NULL;
	PSTR szAttributes[] = {"attributeID", "attributeSyntax", "systemFlags", NULL}, *pszSyntaxOid, *pszFlag;
	OssEncodedOID oid;
	
	attribute->dwSyntax = 0;
	if(kull_m_string_sprintf(&attributesFilter, L"(&(objectclass=attributeSchema)(lDAPDisplayName=%s))", attribute->szAttributeName))
	{
		dwErr = ldap_search_sW(info->ld, info->szConfigurationNamingContext, LDAP_SCOPE_SUBTREE, attributesFilter, NULL, FALSE, &pAttributeMessage);
		if(dwErr == LDAP_SUCCESS)
		{
			if(ldap_count_entries(info->ld, pAttributeMessage) == 1)
			{
				if(attribute->Oid)
					LocalFree(attribute->Oid);
				attribute->Oid =  kuhl_m_lsadump_dcshadow_getSingleTextAttrA(info->ld, pAttributeMessage, szAttributes[0]);
				pszSyntaxOid = ldap_get_valuesA(info->ld, pAttributeMessage, szAttributes[1]);
				if(pszSyntaxOid)
				{
					if(kull_m_asn1_DotVal2Eoid(*pszSyntaxOid, &oid))
					{
						if(oid.length == 3)
							attribute->dwSyntax = (oid.value[0] << 16) + (oid.value[1] << 8) + oid.value[2];
						else PRINT_ERROR(L"oid is invalid %S\n", pszSyntaxOid);
						kull_m_asn1_freeEnc(oid.value);
					}
					ldap_value_freeA(pszSyntaxOid);
				}
				pszFlag = ldap_get_valuesA(info->ld, pAttributeMessage, szAttributes[2]);
				if(pszFlag)
				{
					DWORD systemFlag = strtoul(*pszFlag, NULL, 10);
					if(systemFlag & 1) // FLAG_ATTR_NOT_REPLICATED
						kprintf(L" FLAG_ATTR_NOT_REPLICATED\n");
					if(systemFlag & 4) // FLAG_ATTR_IS_CONSTRUCTED
						kprintf(L" FLAG_ATTR_IS_CONSTRUCTED\n");
					ldap_value_freeA(pszFlag);
				}
			}
			else PRINT_ERROR(L"attribute does not exist\n");
			ldap_msgfree(pAttributeMessage);
		}
		else PRINT_ERROR(L"ldap_search_s 0x%x (%u)\n", dwErr, dwErr);
		LocalFree(attributesFilter);
	}
	return attribute->dwSyntax != 0;
}