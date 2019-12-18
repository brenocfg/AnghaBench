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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {char* member_1; int /*<<< orphan*/ ** member_2; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  TYPE_1__* PLDAPMod ;
typedef  TYPE_1__ LDAPMod ;
typedef  int /*<<< orphan*/  LDAP ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LDAP_MOD_REPLACE ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_string_sprintf (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_modify_s (int /*<<< orphan*/ *,char*,TYPE_1__**) ; 

ULONG kuhl_m_lsadump_dcshadow_lingering_trigger(LDAP* ld, PWSTR szTargetNTDS, PWSTR szObject)
{
	DWORD dwErr;
	PWSTR szMod[] = {NULL, NULL};
	LDAPMod Modification = {LDAP_MOD_REPLACE , L"removeLingeringObject", szMod};
	PLDAPMod pModification[] = {&Modification, NULL};

	if(kull_m_string_sprintf(szMod, L"%s:%s", szTargetNTDS, szObject))
	{
		if (dwErr = ldap_modify_s(ld, L"", pModification))
			PRINT_ERROR(L"removeLingeringObject 0x%x (%u)\n", dwErr, dwErr);
		LocalFree(szMod[0]);
	}
	return dwErr;
}