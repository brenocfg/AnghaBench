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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  SAM_HANDLE ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  scalar_t__* PULONG ;
typedef  scalar_t__* PSID_NAME_USE ;
typedef  int /*<<< orphan*/  PSAM_HANDLE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  NET_API_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  NERR_GroupNotFound ; 
 int /*<<< orphan*/  NERR_Success ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NetpNtStatusToApiStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SamFreeMemory (scalar_t__*) ; 
 int /*<<< orphan*/  SamLookupNamesInDomain (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__**,scalar_t__**) ; 
 int /*<<< orphan*/  SamOpenAlias (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SidTypeAlias ; 

__attribute__((used)) static
NET_API_STATUS
OpenAliasByName(SAM_HANDLE DomainHandle,
                PUNICODE_STRING AliasName,
                ULONG DesiredAccess,
                PSAM_HANDLE AliasHandle)
{
    PULONG RelativeIds = NULL;
    PSID_NAME_USE Use = NULL;
    NET_API_STATUS ApiStatus = NERR_Success;
    NTSTATUS Status = STATUS_SUCCESS;

    /* Get the RID for the given user name */
    Status = SamLookupNamesInDomain(DomainHandle,
                                    1,
                                    AliasName,
                                    &RelativeIds,
                                    &Use);
    if (!NT_SUCCESS(Status))
    {
        ERR("SamLookupNamesInDomain failed (Status %08lx)\n", Status);
        return NetpNtStatusToApiStatus(Status);
    }

    /* Fail, if it is not an alias account */
    if (Use[0] != SidTypeAlias)
    {
        ERR("Object is not an Alias!\n");
        ApiStatus = NERR_GroupNotFound;
        goto done;
    }

    /* Open the alias account */
    Status = SamOpenAlias(DomainHandle,
                          DesiredAccess,
                          RelativeIds[0],
                          AliasHandle);
    if (!NT_SUCCESS(Status))
    {
        ERR("SamOpenDomain failed (Status %08lx)\n", Status);
        ApiStatus = NetpNtStatusToApiStatus(Status);
        goto done;
    }

done:
    if (RelativeIds != NULL)
        SamFreeMemory(RelativeIds);

    if (Use != NULL)
        SamFreeMemory(Use);

    return ApiStatus;
}