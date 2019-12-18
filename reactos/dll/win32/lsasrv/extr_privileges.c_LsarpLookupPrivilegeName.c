#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t ULONG ;
struct TYPE_9__ {scalar_t__ LowPart; scalar_t__ HighPart; } ;
struct TYPE_12__ {int /*<<< orphan*/  Name; TYPE_1__ Luid; } ;
struct TYPE_11__ {scalar_t__ HighPart; scalar_t__ LowPart; } ;
struct TYPE_10__ {int Length; int MaximumLength; int /*<<< orphan*/ * Buffer; } ;
typedef  int /*<<< orphan*/  RPC_UNICODE_STRING ;
typedef  TYPE_2__* PRPC_UNICODE_STRING ;
typedef  TYPE_3__* PLUID ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 size_t ARRAYSIZE (TYPE_4__*) ; 
 void* MIDL_user_allocate (int) ; 
 int /*<<< orphan*/  MIDL_user_free (TYPE_2__*) ; 
 scalar_t__ SE_MAX_WELL_KNOWN_PRIVILEGE ; 
 scalar_t__ SE_MIN_WELL_KNOWN_PRIVILEGE ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  STATUS_NO_SUCH_PRIVILEGE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 TYPE_4__* WellKnownPrivileges ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wcslen (int /*<<< orphan*/ ) ; 

NTSTATUS
LsarpLookupPrivilegeName(PLUID Value,
                         PRPC_UNICODE_STRING *Name)
{
    PRPC_UNICODE_STRING NameBuffer;
    ULONG Priv;

    if (Value->HighPart != 0 ||
        (Value->LowPart < SE_MIN_WELL_KNOWN_PRIVILEGE ||
         Value->LowPart > SE_MAX_WELL_KNOWN_PRIVILEGE))
    {
        return STATUS_NO_SUCH_PRIVILEGE;
    }

    for (Priv = 0; Priv < ARRAYSIZE(WellKnownPrivileges); Priv++)
    {
        if (Value->LowPart == WellKnownPrivileges[Priv].Luid.LowPart &&
            Value->HighPart == WellKnownPrivileges[Priv].Luid.HighPart)
        {
            NameBuffer = MIDL_user_allocate(sizeof(RPC_UNICODE_STRING));
            if (NameBuffer == NULL)
                return STATUS_NO_MEMORY;

            NameBuffer->Length = wcslen(WellKnownPrivileges[Priv].Name) * sizeof(WCHAR);
            NameBuffer->MaximumLength = NameBuffer->Length + sizeof(WCHAR);

            NameBuffer->Buffer = MIDL_user_allocate(NameBuffer->MaximumLength);
            if (NameBuffer->Buffer == NULL)
            {
                MIDL_user_free(NameBuffer);
                return STATUS_NO_MEMORY;
            }

            wcscpy(NameBuffer->Buffer, WellKnownPrivileges[Priv].Name);

            *Name = NameBuffer;

            return STATUS_SUCCESS;
        }
    }

    return STATUS_NO_SUCH_PRIVILEGE;
}