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
struct TYPE_7__ {int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_8__ {int /*<<< orphan*/  Str; } ;
typedef  TYPE_2__ SDB_TMP_STR ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KEY_SET_VALUE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtDeleteValueKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHIM_INFO (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_OBJECT_NAME_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SdbFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SdbpFreeTempStr (TYPE_2__*) ; 
 int /*<<< orphan*/  SdbpOpenKey (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SdbpResolvePath (TYPE_2__*,int /*<<< orphan*/ ) ; 

BOOL SdbDeletePermLayerKeys(PCWSTR wszPath, BOOL bMachine)
{
    UNICODE_STRING FullKey;
    SDB_TMP_STR LongPath;
    HANDLE KeyHandle;
    NTSTATUS Status;

    if (!SdbpResolvePath(&LongPath, wszPath))
        return FALSE;

    Status = SdbpOpenKey(&FullKey, bMachine, KEY_SET_VALUE, &KeyHandle);
    if (NT_SUCCESS(Status))
    {
        Status = NtDeleteValueKey(KeyHandle, &LongPath.Str);
        if (!NT_SUCCESS(Status))
        {
            SHIM_INFO("Failed to delete value from Key \"%wZ\" Status 0x%lx\n", &FullKey, Status);
            /* This is what we want, so if the key didnt exist, we should not fail :) */
            if (Status == STATUS_OBJECT_NAME_NOT_FOUND)
                Status = STATUS_SUCCESS;
        }
        NtClose(KeyHandle);
        SdbFree(FullKey.Buffer);
    }
    SdbpFreeTempStr(&LongPath);
    return NT_SUCCESS(Status);
}