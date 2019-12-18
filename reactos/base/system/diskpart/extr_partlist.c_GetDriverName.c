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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {char* Port; int /*<<< orphan*/  DriverName; } ;
struct TYPE_6__ {char* Name; int /*<<< orphan*/ * EntryContext; int /*<<< orphan*/  Flags; } ;
typedef  TYPE_1__ RTL_QUERY_REGISTRY_TABLE ;
typedef  int /*<<< orphan*/  QueryTable ;
typedef  TYPE_2__* PDISKENTRY ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_QUERY_REGISTRY_DIRECT ; 
 int /*<<< orphan*/  RTL_REGISTRY_DEVICEMAP ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlQueryRegistryValues (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__**,int) ; 
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static
VOID
GetDriverName(
    PDISKENTRY DiskEntry)
{
    RTL_QUERY_REGISTRY_TABLE QueryTable[2];
    WCHAR KeyName[32];
    NTSTATUS Status;

    RtlInitUnicodeString(&DiskEntry->DriverName,
                         NULL);

    swprintf(KeyName,
             L"\\Scsi\\Scsi Port %lu",
             DiskEntry->Port);

    RtlZeroMemory(&QueryTable,
                  sizeof(QueryTable));

    QueryTable[0].Name = L"Driver";
    QueryTable[0].Flags = RTL_QUERY_REGISTRY_DIRECT;
    QueryTable[0].EntryContext = &DiskEntry->DriverName;

    Status = RtlQueryRegistryValues(RTL_REGISTRY_DEVICEMAP,
                                    KeyName,
                                    QueryTable,
                                    NULL,
                                    NULL);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("RtlQueryRegistryValues() failed (Status %lx)\n", Status);
    }
}