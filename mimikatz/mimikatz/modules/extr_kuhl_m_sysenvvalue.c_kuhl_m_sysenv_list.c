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
struct TYPE_4__ {scalar_t__ ValueLength; scalar_t__ ValueOffset; int /*<<< orphan*/  Attributes; int /*<<< orphan*/  VendorGuid; int /*<<< orphan*/  Name; scalar_t__ NextEntryOffset; } ;
typedef  TYPE_1__* PVARIABLE_NAME_AND_VALUE ;
typedef  scalar_t__ PBYTE ;
typedef  scalar_t__ NTSTATUS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LocalFree (TYPE_1__*) ; 
 scalar_t__ NT_SUCCESS (scalar_t__) ; 
 scalar_t__ NtEnumerateSystemEnvironmentValuesEx (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__) ; 
 scalar_t__ STATUS_BUFFER_TOO_SMALL ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  VARIABLE_INFORMATION_VALUES ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_sysenv_display_attributes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_sysenv_display_vendorGuid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (scalar_t__,scalar_t__,int) ; 

NTSTATUS kuhl_m_sysenv_list(int argc, wchar_t * argv[])
{
	NTSTATUS status;
	PVARIABLE_NAME_AND_VALUE buffer;
	DWORD bufferLen = 0;

	status = NtEnumerateSystemEnvironmentValuesEx(VARIABLE_INFORMATION_VALUES, NULL, &bufferLen);
	if((status == STATUS_BUFFER_TOO_SMALL) && bufferLen)
	{
		if(buffer = (PVARIABLE_NAME_AND_VALUE) LocalAlloc(LPTR, bufferLen))
		{
			status = NtEnumerateSystemEnvironmentValuesEx(VARIABLE_INFORMATION_VALUES, buffer, &bufferLen);
			if(NT_SUCCESS(status))
			{
				for(; buffer; buffer = buffer->NextEntryOffset ? (PVARIABLE_NAME_AND_VALUE) ((PBYTE) buffer + buffer->NextEntryOffset) : NULL)
				{
					kprintf(L"Name       : %s\nVendor GUID: ", buffer->Name);
					kuhl_m_sysenv_display_vendorGuid(&buffer->VendorGuid);
					kprintf(L"\nAttributes : %08x (", buffer->Attributes);
					kuhl_m_sysenv_display_attributes(buffer->Attributes);
					kprintf(L")\nLength     : %u\nData       : ", buffer->ValueLength);
					if(buffer->ValueLength && buffer->ValueOffset)
						kull_m_string_wprintf_hex((PBYTE) buffer + buffer->ValueOffset, buffer->ValueLength, 1);
					kprintf(L"\n\n");
				}
			}
			else PRINT_ERROR(L"NtEnumerateSystemEnvironmentValuesEx(data): 0x%08x\n", status);
			LocalFree(buffer);
		}
	}
	else PRINT_ERROR(L"NtEnumerateSystemEnvironmentValuesEx(size): 0x%08x\n", status);
	return STATUS_SUCCESS;
}