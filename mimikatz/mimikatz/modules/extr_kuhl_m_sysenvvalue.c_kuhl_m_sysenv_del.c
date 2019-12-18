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
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 char* MIMIKATZ ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtSetSystemEnvironmentValueEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 int /*<<< orphan*/  RtlGUIDFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_VARIABLE_NOT_FOUND ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_sysenv_display_attributes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_sysenv_display_vendorGuid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wcstoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_sysenv_del(int argc, wchar_t * argv[])
{
	NTSTATUS status;
	LPCWSTR szName, szGuid, szAttributes;
	UNICODE_STRING uName, uGuid;
	GUID guid;
	DWORD attributes;

	kull_m_string_args_byName(argc, argv, L"name", &szName, MIMIKATZ);
	kull_m_string_args_byName(argc, argv, L"guid", &szGuid, L"{b16b00b5-cafe-babe-0ee0-dabadabad000}");
	kull_m_string_args_byName(argc, argv, L"attributes", &szAttributes, L"1");

	RtlInitUnicodeString(&uName, szName);
	RtlInitUnicodeString(&uGuid, szGuid);
	attributes = wcstoul(szAttributes, NULL, 0);

	status = RtlGUIDFromString(&uGuid, &guid);
	if(NT_SUCCESS(status))
	{
		kprintf(L"Name       : %wZ\nVendor GUID: ", &uName);
		kuhl_m_sysenv_display_vendorGuid(&guid);
		kprintf(L"\nAttributes : %08x (", attributes);
		kuhl_m_sysenv_display_attributes(attributes);
		kprintf(L")\n");

		status = NtSetSystemEnvironmentValueEx(&uName, &guid, NULL, 0, attributes);
		if(NT_SUCCESS(status))
			kprintf(L"> OK!\n");
		else if(status == STATUS_VARIABLE_NOT_FOUND)
			PRINT_ERROR(L"System Environment Variable not found.\n");
		else PRINT_ERROR(L"NtSetSystemEnvironmentValueEx(data): 0x%08x\n", status);
	}
	else PRINT_ERROR(L"RtlGUIDFromString: 0x%08x\n", status);
	return STATUS_SUCCESS;
}