#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  SID_NAME_USE ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/  PSID ;
typedef  int /*<<< orphan*/ * PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ ConvertStringSidToSid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IsValidSid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_displaySID (int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_token_getNameDomainFromSID (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_token_getSidDomainFromName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_token_getSidNameUse (int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_sid_lookup(int argc, wchar_t * argv[])
{
	PWSTR name, domain;
	PSID pSid;
	SID_NAME_USE nameUse;
	PCWCHAR szName, szSystem = NULL;
	kull_m_string_args_byName(argc, argv, L"system", &szSystem, NULL);

	if(kull_m_string_args_byName(argc, argv, L"sid", &szName, NULL))
	{
		if(ConvertStringSidToSid(szName, &pSid))
		{
			kprintf(L"SID   : %s\n", szName);
			if(IsValidSid(pSid))
			{
				if(kull_m_token_getNameDomainFromSID(pSid, &name, &domain, &nameUse, szSystem))
				{
					kprintf(L"Type  : %s\n"
						L"Domain: %s\n"
						L"Name  : %s\n", kull_m_token_getSidNameUse(nameUse), domain, name);
					LocalFree(name);
					LocalFree(domain);
				}
				else PRINT_ERROR_AUTO(L"kull_m_token_getNameDomainFromSID");
			}
			else PRINT_ERROR(L"Invalid SID\n");
			LocalFree(pSid);
		}
		else PRINT_ERROR_AUTO(L"ConvertStringSidToSid");
	}
	else if(kull_m_string_args_byName(argc, argv, L"name", &szName, NULL))
	{
		kprintf(L"Name  : %s\n", szName);
		if(kull_m_token_getSidDomainFromName(szName, &pSid, &domain, &nameUse, szSystem))
		{
			kprintf(L"Type  : %s\n"
				L"Domain: %s\n"
				L"SID   : ", kull_m_token_getSidNameUse(nameUse), domain);
			kull_m_string_displaySID(pSid);
			kprintf(L"\n");
			LocalFree(pSid);
			LocalFree(domain);
		}
		else PRINT_ERROR_AUTO(L"kull_m_token_getSidDomainFromName");
	}
	else PRINT_ERROR(L"/sid or /name is missing\n");

	return STATUS_SUCCESS;
}