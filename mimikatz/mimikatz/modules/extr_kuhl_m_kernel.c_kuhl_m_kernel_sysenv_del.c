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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_4__ {int Attributes; int /*<<< orphan*/ * Name; scalar_t__ ValueOffset; scalar_t__ ValueLength; int /*<<< orphan*/  VendorGuid; } ;
typedef  TYPE_1__* PMIMIDRV_VARIABLE_NAME_AND_VALUE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;

/* Variables and functions */
 int FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOCTL_MIMIDRV_SYSENVSET ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (TYPE_1__*) ; 
 int /*<<< orphan*/  MIMIDRV_VARIABLE_NAME_AND_VALUE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Name ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RtlGUIDFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_sysenv_display_attributes (int) ; 
 int /*<<< orphan*/  kuhl_m_sysenv_display_vendorGuid (int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_kernel_mimidrv_simple_output (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ **,char*) ; 
 scalar_t__ wcslen (int /*<<< orphan*/ *) ; 
 int wcstoul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_kernel_sysenv_del(int argc, wchar_t * argv[])
{
	NTSTATUS status;
	LPCWSTR szName, szGuid, szAttributes;
	UNICODE_STRING uName, uGuid;
	GUID guid;
	DWORD attributes, nameLen, structSize;
	PMIMIDRV_VARIABLE_NAME_AND_VALUE vnv;

	kull_m_string_args_byName(argc, argv, L"name", &szName, L"Kernel_Lsa_Ppl_Config");
	kull_m_string_args_byName(argc, argv, L"guid", &szGuid, L"{77fa9abd-0359-4d32-bd60-28f4e78f784b}");
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
		kprintf(L")\n\n");

		nameLen = ((DWORD) wcslen(szName) + 1) * sizeof(wchar_t);
		structSize = FIELD_OFFSET(MIMIDRV_VARIABLE_NAME_AND_VALUE, Name) + nameLen;
		if(vnv = (PMIMIDRV_VARIABLE_NAME_AND_VALUE) LocalAlloc(LPTR, structSize))
		{
			vnv->Attributes = attributes;
			RtlCopyMemory(&vnv->VendorGuid, &guid, sizeof(GUID));
			vnv->ValueLength = 0;
			vnv->ValueOffset = 0;
			RtlCopyMemory(vnv->Name, szName, nameLen);
			if(kull_m_kernel_mimidrv_simple_output(IOCTL_MIMIDRV_SYSENVSET, vnv, structSize))
				kprintf(L"> OK!\n");
			LocalFree(vnv);
		}
	}
	else PRINT_ERROR(L"RtlGUIDFromString: 0x%08x\n", status);
	return STATUS_SUCCESS;
}