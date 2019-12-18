#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bv_len; int /*<<< orphan*/  bv_val; } ;
typedef  char* PWCHAR ;
typedef  int /*<<< orphan*/ * PLDAPMessage ;
typedef  int /*<<< orphan*/  PCWCHAR ;
typedef  TYPE_1__* PBERVAL ;
typedef  int /*<<< orphan*/  LDAP ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LDAP_SCOPE_BASE ; 
 scalar_t__ LDAP_SUCCESS ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 char* kull_m_string_qad_ansi_c_to_unicode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ldap_count_entries (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ldap_count_values_len (TYPE_1__**) ; 
 TYPE_1__** ldap_get_values_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 scalar_t__ ldap_search_s (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ldap_value_free_len (TYPE_1__**) ; 

PWCHAR kull_m_ldap_getRootDomainNamingContext(PCWCHAR nc, LDAP *ld)
{
	DWORD dwErr;
	PWCHAR rootAttr[] = {nc ? (PWCHAR) nc : L"rootDomainNamingContext", NULL}, ret = NULL;
	PLDAPMessage pMessage = NULL;
	PBERVAL *pBerVal;

	dwErr = ldap_search_s(ld, NULL, LDAP_SCOPE_BASE, L"(dn=RootDSE)", rootAttr, FALSE, &pMessage);
	if(dwErr == LDAP_SUCCESS)
	{
		if(ldap_count_entries(ld, pMessage) == 1)
		{
			if(pBerVal = ldap_get_values_len(ld, pMessage, rootAttr[0]))
			{
				if(ldap_count_values_len(pBerVal) == 1)
					ret = kull_m_string_qad_ansi_c_to_unicode(pBerVal[0]->bv_val, pBerVal[0]->bv_len);
				else PRINT_ERROR(L"ldap_get_values_len is NOT 1\n");
				ldap_value_free_len(pBerVal);
			}
		}
		else PRINT_ERROR(L"ldap_count_entries is NOT 1\n");
	}
	else PRINT_ERROR(L"ldap_search_s 0x%x (%u)\n", dwErr, dwErr);
	if(pMessage)
		ldap_msgfree(pMessage);
	return ret;
}