#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  Buffer; int /*<<< orphan*/  MaximumLength; int /*<<< orphan*/  Length; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  scalar_t__ ULONG ;
struct TYPE_8__ {int /*<<< orphan*/  Name; int /*<<< orphan*/  NameLength; } ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  TYPE_2__* PKEY_NAME_INFORMATION ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  KeyNameInformation ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 scalar_t__ NtQueryKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  RTL_DUPLICATE_UNICODE_STRING_NULL_TERMINATE ; 
 TYPE_2__* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RtlDuplicateUnicodeString (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  RtlNtStatusToDosError (scalar_t__) ; 
 scalar_t__ STATUS_BUFFER_TOO_SMALL ; 

__attribute__((used)) static
LONG
GetKeyName(HKEY hKey, PUNICODE_STRING KeyName)
{
    UNICODE_STRING InfoName;
    PKEY_NAME_INFORMATION NameInformation;
    ULONG InfoLength;
    NTSTATUS Status;

    /* Get info length */
    InfoLength = 0;
    Status = NtQueryKey(hKey, KeyNameInformation, NULL, 0, &InfoLength);
    if (Status != STATUS_BUFFER_TOO_SMALL)
    {
        ERR("NtQueryKey returned unexpected Status: 0x%08x\n", Status);
        return RtlNtStatusToDosError(Status);
    }

    /* Get it for real */
    NameInformation = RtlAllocateHeap(RtlGetProcessHeap(), 0, InfoLength);
    if (NameInformation == NULL)
    {
        ERR("Failed to allocate %lu bytes", InfoLength);
        return ERROR_NOT_ENOUGH_MEMORY;
    }

    Status = NtQueryKey(hKey, KeyNameInformation, NameInformation, InfoLength, &InfoLength);
    if (!NT_SUCCESS(Status))
    {
        RtlFreeHeap(RtlGetProcessHeap(), 0, NameInformation);
        ERR("NtQueryKey failed: 0x%08x\n", Status);
        return RtlNtStatusToDosError(Status);
    }

    /* Make it a proper UNICODE_STRING */
    InfoName.Length = NameInformation->NameLength;
    InfoName.MaximumLength = NameInformation->NameLength;
    InfoName.Buffer = NameInformation->Name;

    Status = RtlDuplicateUnicodeString(RTL_DUPLICATE_UNICODE_STRING_NULL_TERMINATE, &InfoName, KeyName);
    if (!NT_SUCCESS(Status))
    {
        RtlFreeHeap(RtlGetProcessHeap(), 0, NameInformation);
        ERR("RtlDuplicateUnicodeString failed: 0x%08x\n", Status);
        return RtlNtStatusToDosError(Status);
    }

    RtlFreeHeap(RtlGetProcessHeap(), 0, NameInformation);

    return ERROR_SUCCESS;
}