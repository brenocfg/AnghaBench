#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  size_t ULONG ;
struct TYPE_11__ {scalar_t__ Use; int DomainIndex; scalar_t__ Flags; int /*<<< orphan*/ * Sid; } ;
struct TYPE_10__ {scalar_t__ Length; } ;
struct TYPE_9__ {scalar_t__ Use; int /*<<< orphan*/ * Sid; int /*<<< orphan*/  AccountName; int /*<<< orphan*/  DomainName; } ;
typedef  TYPE_1__* PWELL_KNOWN_SID ;
typedef  int /*<<< orphan*/ * PUNICODE_STRING ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  TYPE_2__* PRPC_UNICODE_STRING ;
typedef  TYPE_3__* PLSAPR_TRANSLATED_SID_EX2 ;
typedef  int /*<<< orphan*/  PLSAPR_REFERENCED_DOMAIN_LIST ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AccountDomainName ; 
 int /*<<< orphan*/ * AccountDomainSid ; 
 int /*<<< orphan*/  BuiltinDomainName ; 
 int /*<<< orphan*/ * BuiltinDomainSid ; 
 int /*<<< orphan*/ * CreateDomainSidFromAccountSid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LsapAddDomainToDomainsList (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 void* LsapCopySid (int /*<<< orphan*/ *) ; 
 TYPE_1__* LsapLookupIsolatedWellKnownName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MIDL_user_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_CONSTANT_STRING (char*) ; 
 scalar_t__ RtlEqualUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ SidTypeDomain ; 
 scalar_t__ SidTypeUnknown ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
NTSTATUS
LsapLookupIsolatedNames(DWORD Count,
                        PRPC_UNICODE_STRING DomainNames,
                        PRPC_UNICODE_STRING AccountNames,
                        PLSAPR_REFERENCED_DOMAIN_LIST DomainsBuffer,
                        PLSAPR_TRANSLATED_SID_EX2 SidsBuffer,
                        PULONG Mapped)
{
    UNICODE_STRING EmptyDomainName = RTL_CONSTANT_STRING(L"");
    PWELL_KNOWN_SID ptr, ptr2;
    PSID DomainSid;
    ULONG DomainIndex;
    ULONG i;
    NTSTATUS Status = STATUS_SUCCESS;

    for (i = 0; i < Count; i++)
    {
        /* Ignore names which were already mapped */
        if (SidsBuffer[i].Use != SidTypeUnknown)
            continue;

        /* Ignore fully qualified account names */
        if (DomainNames[i].Length != 0)
            continue;

        TRACE("Mapping name: %wZ\n", &AccountNames[i]);

        /* Look-up all well-known names */
        ptr = LsapLookupIsolatedWellKnownName((PUNICODE_STRING)&AccountNames[i]);
        if (ptr != NULL)
        {
            SidsBuffer[i].Use = ptr->Use;
            SidsBuffer[i].Sid = LsapCopySid(ptr->Sid);
            if (SidsBuffer[i].Sid == NULL)
            {
                Status = STATUS_INSUFFICIENT_RESOURCES;
                goto done;
            }

            SidsBuffer[i].DomainIndex = -1;
            SidsBuffer[i].Flags = 0;

            if (ptr->Use == SidTypeDomain)
            {
                Status = LsapAddDomainToDomainsList(DomainsBuffer,
                                                    &ptr->AccountName,
                                                    ptr->Sid,
                                                    &DomainIndex);
                if (!NT_SUCCESS(Status))
                    goto done;

                SidsBuffer[i].DomainIndex = DomainIndex;
            }
            else
            {
                ptr2= LsapLookupIsolatedWellKnownName(&ptr->DomainName);
                if (ptr2 != NULL)
                {
                    Status = LsapAddDomainToDomainsList(DomainsBuffer,
                                                        &ptr2->AccountName,
                                                        ptr2->Sid,
                                                        &DomainIndex);
                    if (!NT_SUCCESS(Status))
                        goto done;

                    SidsBuffer[i].DomainIndex = DomainIndex;
                }
                else
                {
                    DomainSid = CreateDomainSidFromAccountSid(ptr->Sid);
                    if (DomainSid == NULL)
                    {
                        Status = STATUS_INSUFFICIENT_RESOURCES;
                        goto done;
                    }

                    Status = LsapAddDomainToDomainsList(DomainsBuffer,
                                                        &EmptyDomainName,
                                                        DomainSid,
                                                        &DomainIndex);

                    if (DomainSid != NULL)
                    {
                        MIDL_user_free(DomainSid);
                        DomainSid = NULL;
                    }

                    if (!NT_SUCCESS(Status))
                        goto done;

                    SidsBuffer[i].DomainIndex = DomainIndex;
                }
            }

            (*Mapped)++;
            continue;
        }

        /* Look-up the built-in domain */
        if (RtlEqualUnicodeString((PUNICODE_STRING)&AccountNames[i], &BuiltinDomainName, TRUE))
        {
            SidsBuffer[i].Use = SidTypeDomain;
            SidsBuffer[i].Sid = LsapCopySid(BuiltinDomainSid);
            if (SidsBuffer[i].Sid == NULL)
            {
                Status = STATUS_INSUFFICIENT_RESOURCES;
                goto done;
            }

            SidsBuffer[i].DomainIndex = -1;
            SidsBuffer[i].Flags = 0;

            Status = LsapAddDomainToDomainsList(DomainsBuffer,
                                                &BuiltinDomainName,
                                                BuiltinDomainSid,
                                                &DomainIndex);
            if (!NT_SUCCESS(Status))
                goto done;

            SidsBuffer[i].DomainIndex = DomainIndex;

            (*Mapped)++;
            continue;
        }

        /* Look-up the account domain */
        if (RtlEqualUnicodeString((PUNICODE_STRING)&AccountNames[i], &AccountDomainName, TRUE))
        {
            SidsBuffer[i].Use = SidTypeDomain;
            SidsBuffer[i].Sid = LsapCopySid(AccountDomainSid);
            if (SidsBuffer[i].Sid == NULL)
            {
                Status = STATUS_INSUFFICIENT_RESOURCES;
                goto done;
            }
            SidsBuffer[i].DomainIndex = -1;
            SidsBuffer[i].Flags = 0;

            Status = LsapAddDomainToDomainsList(DomainsBuffer,
                                                &AccountDomainName,
                                                AccountDomainSid,
                                                &DomainIndex);
            if (!NT_SUCCESS(Status))
                goto done;

            SidsBuffer[i].DomainIndex = DomainIndex;

            (*Mapped)++;
            continue;
        }

        /* FIXME: Look-up the primary domain */

        /* FIXME: Look-up the trusted domains */

    }

done:

    return Status;
}