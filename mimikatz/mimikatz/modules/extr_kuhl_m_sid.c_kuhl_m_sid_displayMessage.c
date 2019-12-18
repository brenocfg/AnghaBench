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
struct TYPE_4__ {int /*<<< orphan*/  bv_len; scalar_t__ bv_val; } ;
typedef  int /*<<< orphan*/  SID_NAME_USE ;
typedef  scalar_t__ PWCHAR ;
typedef  scalar_t__ PLDAPMessage ;
typedef  int /*<<< orphan*/  PLDAP ;
typedef  TYPE_1__* PBERVAL ;
typedef  int /*<<< orphan*/  LPGUID ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BerElement ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 scalar_t__ _wcsicmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  ber_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_string_displayGUID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_displaySID (scalar_t__) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kull_m_token_getNameDomainFromSID (scalar_t__,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_token_getSidNameUse (int /*<<< orphan*/ ) ; 
 scalar_t__ ldap_first_attribute (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **) ; 
 scalar_t__ ldap_first_entry (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ldap_get_dn (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__** ldap_get_values_len (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ldap_memfree (scalar_t__) ; 
 scalar_t__ ldap_next_attribute (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ldap_next_entry (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ldap_value_free_len (TYPE_1__**) ; 

void kuhl_m_sid_displayMessage(PLDAP ld, PLDAPMessage pMessage)
{
	PLDAPMessage pEntry;
	PWCHAR pAttribute, name, domain;
	BerElement* pBer = NULL;
	PBERVAL *pBerVal;
	DWORD i;
	SID_NAME_USE nameUse;

	for(pEntry = ldap_first_entry(ld, pMessage); pEntry; pEntry = ldap_next_entry(ld, pEntry))
	{
		kprintf(L"\n%s\n", ldap_get_dn(ld, pEntry));
		for(pAttribute = ldap_first_attribute(ld, pEntry, &pBer); pAttribute; pAttribute = ldap_next_attribute(ld, pEntry, pBer))
		{
			kprintf(L"  %s: ", pAttribute);
			if(pBerVal = ldap_get_values_len(ld, pEntry, pAttribute))
			{
				if(
					(_wcsicmp(pAttribute, L"name") == 0) ||
					(_wcsicmp(pAttribute, L"sAMAccountName") == 0)
					)
				{
					kprintf(L"%*S\n", pBerVal[0]->bv_len, pBerVal[0]->bv_val);
				}
				else if((_wcsicmp(pAttribute, L"objectSid") == 0))
				{
					kull_m_string_displaySID(pBerVal[0]->bv_val);
					kprintf(L"\n");
				}
				else if((_wcsicmp(pAttribute, L"objectGUID") == 0))
				{
					kull_m_string_displayGUID((LPGUID) pBerVal[0]->bv_val);
					kprintf(L"\n");
				}
				else 
				{
					for(i = 0; pBerVal[i]; i++)
					{
						kprintf(L"\n   [%u] ", i);
						if((_wcsicmp(pAttribute, L"sIDHistory") == 0))
						{
							kull_m_string_displaySID(pBerVal[i]->bv_val);
							if(kull_m_token_getNameDomainFromSID(pBerVal[i]->bv_val, &name, &domain, &nameUse, NULL))
							{
								kprintf(L" ( %s -- %s\\%s )", kull_m_token_getSidNameUse(nameUse), domain, name);
								LocalFree(name);
								LocalFree(domain);
							}
						}
						else kull_m_string_wprintf_hex(pBerVal[i]->bv_val, pBerVal[i]->bv_len, 1);
					}
					kprintf(L"\n");
				}
				ldap_value_free_len(pBerVal);
			}
			ldap_memfree(pAttribute);
		}
		if(pBer)
			ber_free(pBer, 0);
	}
}