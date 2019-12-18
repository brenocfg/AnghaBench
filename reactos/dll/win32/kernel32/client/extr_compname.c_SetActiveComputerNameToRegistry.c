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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BaseSetLastNTError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int MAXULONG ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtCreateKey (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtFlushKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtOpenKey (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtSetValueKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  REG_OPTION_VOLATILE ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int wcslen (scalar_t__) ; 

__attribute__((used)) static
BOOL
SetActiveComputerNameToRegistry(LPCWSTR RegistryKey,
                                LPCWSTR SubKey,
                                LPCWSTR ValueNameStr,
                                LPCWSTR lpBuffer)
{
    OBJECT_ATTRIBUTES ObjectAttributes;
    UNICODE_STRING KeyName;
    UNICODE_STRING ValueName;
    HANDLE KeyHandle, SubKeyHandle;
    SIZE_T StringLength;
    ULONG Disposition;
    NTSTATUS Status;

    StringLength = wcslen(lpBuffer);
    if (StringLength > ((MAXULONG / sizeof(WCHAR)) - 1))
    {
        return FALSE;
    }

    RtlInitUnicodeString(&KeyName, RegistryKey);
    InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);

    Status = NtOpenKey(&KeyHandle,
                       KEY_WRITE,
                       &ObjectAttributes);
    if (!NT_SUCCESS(Status))
    {
        BaseSetLastNTError(Status);
        return FALSE;
    }

    RtlInitUnicodeString(&KeyName, SubKey);
    InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               KeyHandle,
                               NULL);

    Status = NtCreateKey(&SubKeyHandle,
                         KEY_WRITE,
                         &ObjectAttributes,
                         0,
                         NULL,
                         REG_OPTION_VOLATILE,
                         &Disposition);
    if (!NT_SUCCESS(Status))
    {
        NtClose(KeyHandle);
        BaseSetLastNTError(Status);
        return FALSE;
    }

    RtlInitUnicodeString(&ValueName, ValueNameStr);

    Status = NtSetValueKey(SubKeyHandle,
                           &ValueName,
                           0,
                           REG_SZ,
                           (PVOID)lpBuffer,
                           (StringLength + 1) * sizeof(WCHAR));
    if (!NT_SUCCESS(Status))
    {
        NtClose(SubKeyHandle);
        NtClose(KeyHandle);
        BaseSetLastNTError(Status);
        return FALSE;
    }

    NtFlushKey(SubKeyHandle);
    NtClose(SubKeyHandle);
    NtClose(KeyHandle);

    return TRUE;
}