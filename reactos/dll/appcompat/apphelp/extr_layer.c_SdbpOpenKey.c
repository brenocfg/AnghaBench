#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ USHORT ;
struct TYPE_12__ {scalar_t__ Length; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_13__ {int /*<<< orphan*/ * Buffer; scalar_t__ Length; scalar_t__ MaximumLength; } ;
typedef  TYPE_2__* PUNICODE_STRING ;
typedef  int /*<<< orphan*/  PHANDLE ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ BOOL ;
typedef  int ACCESS_MASK ;

/* Variables and functions */
 int /*<<< orphan*/ * APPCOMPAT_LAYER_KEY ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtOpenKey (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  REGISTRY_MACHINE ; 
 int /*<<< orphan*/  RTL_INIT_OBJECT_ATTRIBUTES (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlAppendUnicodeStringToString (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  RtlAppendUnicodeToString (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RtlFormatCurrentUserKeyPath (TYPE_1__*) ; 
 int /*<<< orphan*/  RtlFreeUnicodeString (TYPE_1__*) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHIM_ERR (char*,TYPE_2__*,...) ; 
 int /*<<< orphan*/ * SdbAlloc (scalar_t__) ; 
 int /*<<< orphan*/  SdbFree (int /*<<< orphan*/ *) ; 
 scalar_t__ SdbpStrsize (int /*<<< orphan*/  const*) ; 
 int Wow64QueryFlag () ; 

NTSTATUS SdbpOpenKey(PUNICODE_STRING FullPath, BOOL bMachine, ACCESS_MASK Access, PHANDLE KeyHandle)
{
    UNICODE_STRING BasePath;
    const WCHAR* LayersKey = APPCOMPAT_LAYER_KEY;
    OBJECT_ATTRIBUTES ObjectLayer = RTL_INIT_OBJECT_ATTRIBUTES(FullPath, OBJ_CASE_INSENSITIVE);
    NTSTATUS Status;
    FullPath->Buffer = NULL;
    FullPath->Length = FullPath->MaximumLength = 0;
    if (bMachine)
    {
        RtlInitUnicodeString(&BasePath, REGISTRY_MACHINE);
    }
    else
    {
        Status = RtlFormatCurrentUserKeyPath(&BasePath);
        if (!NT_SUCCESS(Status))
        {
            SHIM_ERR("Unable to acquire user registry key, Error: 0x%lx\n", Status);
            return Status;
        }
    }
    FullPath->MaximumLength = (USHORT)(BasePath.Length + SdbpStrsize(LayersKey));
    FullPath->Buffer = SdbAlloc(FullPath->MaximumLength);
    FullPath->Length = 0;
    RtlAppendUnicodeStringToString(FullPath, &BasePath);
    if (!bMachine)
        RtlFreeUnicodeString(&BasePath);
    RtlAppendUnicodeToString(FullPath, LayersKey);

    Status = NtOpenKey(KeyHandle, Access | Wow64QueryFlag(), &ObjectLayer);
    if (!NT_SUCCESS(Status))
    {
        SHIM_ERR("Unable to open Key  \"%wZ\" Status 0x%lx\n", FullPath, Status);
        SdbFree(FullPath->Buffer);
        FullPath->Buffer = NULL;
    }
    return Status;
}