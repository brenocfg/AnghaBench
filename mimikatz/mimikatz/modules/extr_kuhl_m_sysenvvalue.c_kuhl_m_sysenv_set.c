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
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 char* MIMIKATZ ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtSetSystemEnvironmentValueEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlGUIDFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_sysenv_display_attributes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_sysenv_display_vendorGuid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ kull_m_string_stringToHexBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wcstoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_sysenv_set(int argc, wchar_t * argv[])
{
	NTSTATUS status;
	LPCWSTR szName, szGuid, szAttributes, szData;
	UNICODE_STRING uName, uGuid;
	GUID guid;
	LPBYTE hex;
	DWORD size, attributes;

	kull_m_string_args_byName(argc, argv, L"name", &szName, MIMIKATZ);
	kull_m_string_args_byName(argc, argv, L"guid", &szGuid, L"{b16b00b5-cafe-babe-0ee0-dabadabad000}");
	kull_m_string_args_byName(argc, argv, L"attributes", &szAttributes, L"1");
	kull_m_string_args_byName(argc, argv, L"data", &szData, L"410020004c00610020005600690065002c002000410020004c00270041006d006f00750072000000");

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
		if(kull_m_string_stringToHexBuffer(szData, &hex, &size))
		{
			kprintf(L"Length     : %u\nData       : ", size);
			kull_m_string_wprintf_hex(hex, size, 1);
			kprintf(L"\n\n");
			status = NtSetSystemEnvironmentValueEx(&uName, &guid, hex, size, attributes);
			if(NT_SUCCESS(status))
				kprintf(L"> OK!\n");
			else PRINT_ERROR(L"NtSetSystemEnvironmentValueEx(data): 0x%08x\n", status);
			LocalFree(hex);
		}
	}
	else PRINT_ERROR(L"RtlGUIDFromString: 0x%08x\n", status);
	return STATUS_SUCCESS;
}