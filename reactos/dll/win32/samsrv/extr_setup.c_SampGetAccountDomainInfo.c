#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int Length; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PPOLICY_ACCOUNT_DOMAIN_INFO ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_1__ LSA_OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  LSA_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  LsaClose (int /*<<< orphan*/ ) ; 
 scalar_t__ LsaOpenPolicy (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ LsaQueryInformationPolicy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POLICY_VIEW_LOCAL_INFORMATION ; 
 int /*<<< orphan*/  PolicyAccountDomainInformation ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

NTSTATUS
SampGetAccountDomainInfo(PPOLICY_ACCOUNT_DOMAIN_INFO *AccountDomainInfo)
{
    LSA_OBJECT_ATTRIBUTES ObjectAttributes;
    LSA_HANDLE PolicyHandle;
    NTSTATUS Status;

    TRACE("SampGetAccountDomainInfo\n");

    memset(&ObjectAttributes, 0, sizeof(LSA_OBJECT_ATTRIBUTES));
    ObjectAttributes.Length = sizeof(LSA_OBJECT_ATTRIBUTES);

    Status = LsaOpenPolicy(NULL,
                           &ObjectAttributes,
                           POLICY_VIEW_LOCAL_INFORMATION,
                           &PolicyHandle);
    if (Status != STATUS_SUCCESS)
    {
        ERR("LsaOpenPolicy failed (Status: 0x%08lx)\n", Status);
        return Status;
    }

    Status = LsaQueryInformationPolicy(PolicyHandle,
                                       PolicyAccountDomainInformation,
                                       (PVOID *)AccountDomainInfo);

    LsaClose(PolicyHandle);

    return Status;
}