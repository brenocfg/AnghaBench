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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_5__ {scalar_t__ Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int /*<<< orphan*/ * PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/ * LPCGUID ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  RtlGUIDFromString (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_LsaRetrievePrivateData (int /*<<< orphan*/ *,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_getKeyFromGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_displayGUID (int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_lsadump_bkey(int argc, wchar_t * argv[])
{
	NTSTATUS status;
	UNICODE_STRING secret;
	GUID guid;
	PCWCHAR szGuid = NULL, szSystem = NULL;
	BOOL export = kull_m_string_args_byName(argc, argv, L"export", NULL, NULL);
	BOOL isSecret = kull_m_string_args_byName(argc, argv, L"secret", NULL, NULL);

	kull_m_string_args_byName(argc, argv, L"system", &szSystem, NULL);
	kull_m_string_args_byName(argc, argv, L"guid", &szGuid, NULL);
	if(szGuid)
	{
		RtlInitUnicodeString(&secret, szGuid);
		status = RtlGUIDFromString(&secret, &guid);
		if(NT_SUCCESS(status))
		{
			kprintf(L"\n"); kull_m_string_displayGUID(&guid); kprintf(L" seems to be a valid GUID\n");
			kuhl_m_lsadump_getKeyFromGUID(&guid, export, szSystem, isSecret);
		}
		else PRINT_ERROR(L"Invalid GUID (0x%08x) ; %s\n", status, szGuid);
	}
	else
	{
		kprintf(L"\nCurrent prefered key:       ");
		status = kuhl_m_lsadump_LsaRetrievePrivateData(szSystem, L"G$BCKUPKEY_PREFERRED", &secret, isSecret);
		if(NT_SUCCESS(status))
		{
			kull_m_string_displayGUID((LPCGUID) secret.Buffer); kprintf(L"\n");
			kuhl_m_lsadump_getKeyFromGUID((LPCGUID) secret.Buffer, export, szSystem, isSecret);
			LocalFree(secret.Buffer);
		}
		else PRINT_ERROR(L"kuhl_m_lsadump_LsaRetrievePrivateData: 0x%08x\n", status);

		kprintf(L"\nCompatibility prefered key: ");
		status = kuhl_m_lsadump_LsaRetrievePrivateData(szSystem, L"G$BCKUPKEY_P", &secret, isSecret);
		if(NT_SUCCESS(status))
		{
			kull_m_string_displayGUID((LPCGUID) secret.Buffer); kprintf(L"\n");
			kuhl_m_lsadump_getKeyFromGUID((LPCGUID) secret.Buffer, export, szSystem, isSecret);
			LocalFree(secret.Buffer);
		}
		else PRINT_ERROR(L"kuhl_m_lsadump_LsaRetrievePrivateData: 0x%08x\n", status);
	}
	return STATUS_SUCCESS;
}