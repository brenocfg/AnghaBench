#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {int /*<<< orphan*/  Buffer; } ;
struct TYPE_6__ {scalar_t__* EntryContext; int DefaultLength; scalar_t__* DefaultData; int /*<<< orphan*/  DefaultType; int /*<<< orphan*/  Name; int /*<<< orphan*/  Flags; } ;
typedef  TYPE_1__ RTL_QUERY_REGISTRY_TABLE ;
typedef  int /*<<< orphan*/  QueryTable ;
typedef  TYPE_2__* PUNICODE_STRING ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OfflinePath ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  RTL_QUERY_REGISTRY_DIRECT ; 
 int /*<<< orphan*/  RTL_REGISTRY_ABSOLUTE ; 
 int /*<<< orphan*/  RtlQueryRegistryValues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 

BOOLEAN
IsOffline(PUNICODE_STRING SymbolicName)
{
    NTSTATUS Status;
    ULONG IsOffline, Default;
    RTL_QUERY_REGISTRY_TABLE QueryTable[2];

    /* Prepare to look in the registry to see if
     * given volume is offline
     */
    RtlZeroMemory(QueryTable, sizeof(QueryTable));
    QueryTable[0].Flags = RTL_QUERY_REGISTRY_DIRECT;
    QueryTable[0].Name = SymbolicName->Buffer;
    QueryTable[0].EntryContext = &IsOffline;
    QueryTable[0].DefaultType = REG_DWORD;
    QueryTable[0].DefaultLength = sizeof(ULONG);
    QueryTable[0].DefaultData = &Default;

    Default = 0;

    /* Query status */
    Status = RtlQueryRegistryValues(RTL_REGISTRY_ABSOLUTE,
                                    OfflinePath,
                                    QueryTable,
                                    NULL,
                                    NULL);
    if (!NT_SUCCESS(Status))
    {
        IsOffline = 0;
    }

    return (IsOffline != 0);
}