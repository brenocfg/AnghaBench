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
typedef  int /*<<< orphan*/ * PSECURITY_DESCRIPTOR ;
typedef  scalar_t__ NTSTATUS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,scalar_t__) ; 
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 scalar_t__ RtlAbsoluteToSelfRelativeSD (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/ * RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 scalar_t__ RtlNtStatusToDosError (scalar_t__) ; 
 scalar_t__ STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  pDefaultSD ; 

DWORD
ScmCreateDefaultServiceSD(
    PSECURITY_DESCRIPTOR *ppSecurityDescriptor)
{
    PSECURITY_DESCRIPTOR pRelativeSD = NULL;
    DWORD dwBufferLength = 0;
    NTSTATUS Status;
    DWORD dwError = ERROR_SUCCESS;

    /* Convert the absolute SD to a self-relative SD */
    Status = RtlAbsoluteToSelfRelativeSD(pDefaultSD,
                                         NULL,
                                         &dwBufferLength);
    if (Status != STATUS_BUFFER_TOO_SMALL)
    {
        dwError = RtlNtStatusToDosError(Status);
        goto done;
    }

    DPRINT("BufferLength %lu\n", dwBufferLength);

    pRelativeSD = RtlAllocateHeap(RtlGetProcessHeap(),
                                  HEAP_ZERO_MEMORY,
                                  dwBufferLength);
    if (pRelativeSD == NULL)
    {
        dwError = ERROR_OUTOFMEMORY;
        goto done;
    }
    DPRINT("pRelativeSD %p\n", pRelativeSD);

    Status = RtlAbsoluteToSelfRelativeSD(pDefaultSD,
                                         pRelativeSD,
                                         &dwBufferLength);
    if (!NT_SUCCESS(Status))
    {
        dwError = RtlNtStatusToDosError(Status);
        goto done;
    }

    *ppSecurityDescriptor = pRelativeSD;

done:
    if (dwError != ERROR_SUCCESS)
    {
        if (pRelativeSD != NULL)
            RtlFreeHeap(RtlGetProcessHeap(), 0, pRelativeSD);
    }

    return dwError;
}