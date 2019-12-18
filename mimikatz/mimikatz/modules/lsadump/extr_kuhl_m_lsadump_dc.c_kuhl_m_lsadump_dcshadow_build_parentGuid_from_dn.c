#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_4__ {int bv_len; int /*<<< orphan*/  bv_val; } ;
typedef  scalar_t__ PWSTR ;
typedef  char* PWCHAR ;
typedef  int /*<<< orphan*/ * PLDAPMessage ;
typedef  int /*<<< orphan*/  PLDAP ;
typedef  TYPE_1__* PBERVAL ;
typedef  int /*<<< orphan*/  GUID ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LDAP_SCOPE_BASE ; 
 size_t LDAP_SUCCESS ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRUE ; 
 char** ldap_explode_dn (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__** ldap_get_values_len (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 size_t ldap_search_s (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ldap_value_free (char**) ; 
 int /*<<< orphan*/  ldap_value_free_len (TYPE_1__**) ; 
 scalar_t__ lstrlenW (char*) ; 
 int /*<<< orphan*/  wcscat_s (scalar_t__,size_t,char*) ; 
 scalar_t__ wcsncmp (scalar_t__,char*,int) ; 

BOOL kuhl_m_lsadump_dcshadow_build_parentGuid_from_dn(PLDAP ld, PWSTR szObjectDN, GUID* pParentGuid)
{
	BOOL fSuccess = FALSE;
	PWSTR szParentDN;
	DWORD dwErr, len, i;
	WCHAR** szrdns;
	PWCHAR replAttr[] = {L"objectGUID", NULL};
	PBERVAL *guid;
	PLDAPMessage pMessage = NULL;

	if (wcsncmp(szObjectDN, L"DC=", 3) == 0)
	{
		RtlZeroMemory(pParentGuid, sizeof(GUID));
		return TRUE;
	}

	if ((szrdns = ldap_explode_dn(szObjectDN, 0)) ==  NULL)
	{
		PRINT_ERROR(L"Unable to parse DN (%s)\n", szObjectDN);
		return FALSE;
	}
	len = 1;
	for(i = 1; szrdns[i] != NULL; i++)
	{
		len += (2 + lstrlenW(szrdns[i]));
	}
	szParentDN = (PWSTR) LocalAlloc(LPTR, len * sizeof(WCHAR));
	if (szParentDN)
	{
		for(i = 1; szrdns[i] != NULL; i++)
		{
			if (i > 1)
				wcscat_s(szParentDN, len, L",");
			wcscat_s(szParentDN, len, szrdns[i]);
		}
	}
	ldap_value_free(szrdns);
	if (!szParentDN)
		return FALSE;

	dwErr = ldap_search_s(ld, szParentDN, LDAP_SCOPE_BASE, L"(objectclass=*)", replAttr, FALSE, &pMessage);
	if(dwErr == LDAP_SUCCESS)
	{
		if((guid = ldap_get_values_len(ld, pMessage, replAttr[0])) != NULL && ((*guid)->bv_len == sizeof(GUID)))
		{
			RtlCopyMemory(pParentGuid, (*guid)->bv_val, (*guid)->bv_len);
			fSuccess = TRUE;
			ldap_value_free_len(guid);
		}
		ldap_msgfree(pMessage);
	}
	else
	{
		PRINT_ERROR(L"Parent DN (%s) not found\n", szParentDN);
	}
	LocalFree(szParentDN);
	return fSuccess;
}