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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  SECURITY_DESCRIPTOR ;
typedef  int* PULONG ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  int /*<<< orphan*/ * PSECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/ * PACL ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  ACL ;
typedef  int /*<<< orphan*/  ACCESS_DENIED_ACE ;
typedef  int /*<<< orphan*/  ACCESS_ALLOWED_ACE ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_REVISION ; 
 int /*<<< orphan*/  DOMAIN_ALIAS_RID_ADMINS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  NtAuthority ; 
 int POLICY_ALL_ACCESS ; 
 int POLICY_EXECUTE ; 
 int POLICY_LOOKUP_NAMES ; 
 int POLICY_NOTIFICATION ; 
 int POLICY_VIEW_LOCAL_INFORMATION ; 
 scalar_t__ RtlAbsoluteToSelfRelativeSD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ RtlAddAccessAllowedAce (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ RtlAddAccessDeniedAce (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ RtlAllocateAndInitializeSid (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ RtlCreateAcl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ RtlCreateSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int RtlLengthSid (int /*<<< orphan*/ *) ; 
 scalar_t__ RtlSetDaclSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RtlSetGroupSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RtlSetOwnerSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECURITY_ANONYMOUS_LOGON_RID ; 
 int /*<<< orphan*/  SECURITY_BUILTIN_DOMAIN_RID ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_REVISION ; 
 int /*<<< orphan*/  SECURITY_LOCAL_SERVICE_RID ; 
 int /*<<< orphan*/  SECURITY_LOCAL_SYSTEM_RID ; 
 int /*<<< orphan*/  SECURITY_NETWORK_SERVICE_RID ; 
 int /*<<< orphan*/  SECURITY_WORLD_RID ; 
 scalar_t__ STATUS_BUFFER_TOO_SMALL ; 
 scalar_t__ STATUS_INSUFFICIENT_RESOURCES ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WorldSidAuthority ; 

NTSTATUS
LsapCreatePolicySd(PSECURITY_DESCRIPTOR *PolicySd,
                   PULONG PolicySdSize)
{
    SECURITY_DESCRIPTOR AbsoluteSd;
    PSECURITY_DESCRIPTOR RelativeSd = NULL;
    ULONG RelativeSdSize = 0;
    PSID AnonymousSid = NULL;
    PSID AdministratorsSid = NULL;
    PSID EveryoneSid = NULL;
    PSID LocalServiceSid = NULL;
    PSID NetworkServiceSid = NULL;
    PSID LocalSystemSid = NULL;
    PACL Dacl = NULL;
    ULONG DaclSize;
    NTSTATUS Status;

    if (PolicySd == NULL || PolicySdSize == NULL)
        return STATUS_INVALID_PARAMETER;

    *PolicySd = NULL;
    *PolicySdSize = 0;

    /* Initialize the SD */
    Status = RtlCreateSecurityDescriptor(&AbsoluteSd,
                                         SECURITY_DESCRIPTOR_REVISION);
    if (!NT_SUCCESS(Status))
        return Status;

    Status = RtlAllocateAndInitializeSid(&NtAuthority,
                                         1,
                                         SECURITY_ANONYMOUS_LOGON_RID,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         &AnonymousSid);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = RtlAllocateAndInitializeSid(&NtAuthority,
                                         2,
                                         SECURITY_BUILTIN_DOMAIN_RID,
                                         DOMAIN_ALIAS_RID_ADMINS,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         &AdministratorsSid);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = RtlAllocateAndInitializeSid(&WorldSidAuthority,
                                         1,
                                         SECURITY_WORLD_RID,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         &EveryoneSid);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = RtlAllocateAndInitializeSid(&NtAuthority,
                                         1,
                                         SECURITY_LOCAL_SERVICE_RID,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         &LocalServiceSid);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = RtlAllocateAndInitializeSid(&NtAuthority,
                                         1,
                                         SECURITY_NETWORK_SERVICE_RID,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         &NetworkServiceSid);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = RtlAllocateAndInitializeSid(&NtAuthority,
                                         1,
                                         SECURITY_LOCAL_SYSTEM_RID,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         &LocalSystemSid);
    if (!NT_SUCCESS(Status))
        goto done;

    /* Allocate and initialize the DACL */
    DaclSize = sizeof(ACL) +
               sizeof(ACCESS_DENIED_ACE)  - sizeof(ULONG) + RtlLengthSid(AnonymousSid) +
               sizeof(ACCESS_ALLOWED_ACE) - sizeof(ULONG) + RtlLengthSid(AdministratorsSid) +
               sizeof(ACCESS_ALLOWED_ACE) - sizeof(ULONG) + RtlLengthSid(EveryoneSid) +
               sizeof(ACCESS_ALLOWED_ACE) - sizeof(ULONG) + RtlLengthSid(AnonymousSid) +
               sizeof(ACCESS_ALLOWED_ACE) - sizeof(ULONG) + RtlLengthSid(LocalServiceSid) +
               sizeof(ACCESS_ALLOWED_ACE) - sizeof(ULONG) + RtlLengthSid(NetworkServiceSid);

    Dacl = RtlAllocateHeap(RtlGetProcessHeap(),
                           HEAP_ZERO_MEMORY,
                           DaclSize);
    if (Dacl == NULL)
    {
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto done;
    }

    Status = RtlCreateAcl(Dacl,
                          DaclSize,
                          ACL_REVISION);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = RtlAddAccessDeniedAce(Dacl,
                                   ACL_REVISION,
                                   POLICY_LOOKUP_NAMES,
                                   AnonymousSid);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = RtlAddAccessAllowedAce(Dacl,
                                    ACL_REVISION,
                                    POLICY_ALL_ACCESS | POLICY_NOTIFICATION,
                                    AdministratorsSid);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = RtlAddAccessAllowedAce(Dacl,
                                    ACL_REVISION,
                                    POLICY_EXECUTE,
                                    EveryoneSid);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = RtlAddAccessAllowedAce(Dacl,
                                    ACL_REVISION,
                                    POLICY_LOOKUP_NAMES | POLICY_VIEW_LOCAL_INFORMATION,
                                    AnonymousSid);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = RtlAddAccessAllowedAce(Dacl,
                                    ACL_REVISION,
                                    POLICY_NOTIFICATION,
                                    LocalServiceSid);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = RtlAddAccessAllowedAce(Dacl,
                                    ACL_REVISION,
                                    POLICY_NOTIFICATION,
                                    NetworkServiceSid);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = RtlSetDaclSecurityDescriptor(&AbsoluteSd,
                                          TRUE,
                                          Dacl,
                                          FALSE);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = RtlSetGroupSecurityDescriptor(&AbsoluteSd,
                                           LocalSystemSid,
                                           FALSE);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = RtlSetOwnerSecurityDescriptor(&AbsoluteSd,
                                           AdministratorsSid,
                                           FALSE);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = RtlAbsoluteToSelfRelativeSD(&AbsoluteSd,
                                         RelativeSd,
                                         &RelativeSdSize);
    if (Status != STATUS_BUFFER_TOO_SMALL)
        goto done;

    RelativeSd = RtlAllocateHeap(RtlGetProcessHeap(),
                                 HEAP_ZERO_MEMORY,
                                 RelativeSdSize);
    if (RelativeSd == NULL)
    {
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto done;
    }

    Status = RtlAbsoluteToSelfRelativeSD(&AbsoluteSd,
                                         RelativeSd,
                                         &RelativeSdSize);
    if (!NT_SUCCESS(Status))
        goto done;

    *PolicySd = RelativeSd;
    *PolicySdSize = RelativeSdSize;

done:
    if (Dacl != NULL)
        RtlFreeHeap(RtlGetProcessHeap(), 0, Dacl);

    if (AnonymousSid != NULL)
        RtlFreeHeap(RtlGetProcessHeap(), 0, AnonymousSid);

    if (AdministratorsSid != NULL)
        RtlFreeHeap(RtlGetProcessHeap(), 0, AdministratorsSid);

    if (EveryoneSid != NULL)
        RtlFreeHeap(RtlGetProcessHeap(), 0, EveryoneSid);

    if (LocalServiceSid != NULL)
        RtlFreeHeap(RtlGetProcessHeap(), 0, LocalServiceSid);

    if (NetworkServiceSid != NULL)
        RtlFreeHeap(RtlGetProcessHeap(), 0, NetworkServiceSid);

    if (LocalSystemSid != NULL)
        RtlFreeHeap(RtlGetProcessHeap(), 0, LocalSystemSid);

    if (!NT_SUCCESS(Status))
    {
        if (RelativeSd != NULL)
            RtlFreeHeap(RtlGetProcessHeap(), 0, RelativeSd);
    }

    return Status;
}