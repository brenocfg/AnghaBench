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
typedef  size_t ULONG ;
struct TYPE_7__ {size_t Flag; int /*<<< orphan*/  Name; } ;
struct TYPE_6__ {int Length; int MaximumLength; int /*<<< orphan*/ * Buffer; } ;
typedef  int /*<<< orphan*/  RPC_UNICODE_STRING ;
typedef  TYPE_1__* PRPC_UNICODE_STRING ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 size_t ARRAYSIZE (TYPE_2__*) ; 
 void* MIDL_user_allocate (int) ; 
 int /*<<< orphan*/  MIDL_user_free (TYPE_1__*) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  STATUS_NO_SUCH_PRIVILEGE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 TYPE_2__* WellKnownRights ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wcslen (int /*<<< orphan*/ ) ; 

NTSTATUS
LsapLookupAccountRightName(ULONG RightValue,
                           PRPC_UNICODE_STRING *Name)
{
    PRPC_UNICODE_STRING NameBuffer;
    ULONG i;

    for (i = 0; i < ARRAYSIZE(WellKnownRights); i++)
    {
        if (WellKnownRights[i].Flag == RightValue)
        {
            NameBuffer = MIDL_user_allocate(sizeof(RPC_UNICODE_STRING));
            if (NameBuffer == NULL)
                return STATUS_NO_MEMORY;

            NameBuffer->Length = wcslen(WellKnownRights[i].Name) * sizeof(WCHAR);
            NameBuffer->MaximumLength = NameBuffer->Length + sizeof(WCHAR);

            NameBuffer->Buffer = MIDL_user_allocate(NameBuffer->MaximumLength);
            if (NameBuffer->Buffer == NULL)
            {
                MIDL_user_free(NameBuffer);
                return STATUS_INSUFFICIENT_RESOURCES;
            }

            wcscpy(NameBuffer->Buffer, WellKnownRights[i].Name);

            *Name = NameBuffer;

            return STATUS_SUCCESS;
        }
    }

    return STATUS_NO_SUCH_PRIVILEGE;
}