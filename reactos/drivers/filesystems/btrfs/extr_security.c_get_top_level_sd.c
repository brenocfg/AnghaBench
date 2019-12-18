#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; } ;
struct TYPE_5__ {int /*<<< orphan*/ * sd; TYPE_1__ inode_item; } ;
typedef  TYPE_2__ fcb ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  SECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  ACL ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  PagedPool ; 
 scalar_t__ RtlAbsoluteToSelfRelativeSD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ RtlCreateSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RtlSetDaclSecurityDescriptor (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ RtlSetGroupSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ RtlSetOwnerSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_REVISION ; 
 scalar_t__ STATUS_BUFFER_TOO_SMALL ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  gid_to_sid (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * load_default_acl () ; 
 scalar_t__ uid_to_sid (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void get_top_level_sd(fcb* fcb) {
    NTSTATUS Status;
    SECURITY_DESCRIPTOR sd;
    ULONG buflen;
    ACL* acl = NULL;
    PSID usersid = NULL, groupsid = NULL;

    Status = RtlCreateSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);

    if (!NT_SUCCESS(Status)) {
        ERR("RtlCreateSecurityDescriptor returned %08x\n", Status);
        goto end;
    }

    Status = uid_to_sid(fcb->inode_item.st_uid, &usersid);
    if (!NT_SUCCESS(Status)) {
        ERR("uid_to_sid returned %08x\n", Status);
        goto end;
    }

    Status = RtlSetOwnerSecurityDescriptor(&sd, usersid, false);

    if (!NT_SUCCESS(Status)) {
        ERR("RtlSetOwnerSecurityDescriptor returned %08x\n", Status);
        goto end;
    }

    gid_to_sid(fcb->inode_item.st_gid, &groupsid);
    if (!groupsid) {
        ERR("out of memory\n");
        goto end;
    }

    Status = RtlSetGroupSecurityDescriptor(&sd, groupsid, false);

    if (!NT_SUCCESS(Status)) {
        ERR("RtlSetGroupSecurityDescriptor returned %08x\n", Status);
        goto end;
    }

    acl = load_default_acl();

    if (!acl) {
        ERR("out of memory\n");
        goto end;
    }

    Status = RtlSetDaclSecurityDescriptor(&sd, true, acl, false);

    if (!NT_SUCCESS(Status)) {
        ERR("RtlSetDaclSecurityDescriptor returned %08x\n", Status);
        goto end;
    }

    // FIXME - SACL_SECURITY_INFORMATION

    buflen = 0;

    // get sd size
    Status = RtlAbsoluteToSelfRelativeSD(&sd, NULL, &buflen);
    if (Status != STATUS_SUCCESS && Status != STATUS_BUFFER_TOO_SMALL) {
        ERR("RtlAbsoluteToSelfRelativeSD 1 returned %08x\n", Status);
        goto end;
    }

    if (buflen == 0 || Status == STATUS_SUCCESS) {
        TRACE("RtlAbsoluteToSelfRelativeSD said SD is zero-length\n");
        goto end;
    }

    fcb->sd = ExAllocatePoolWithTag(PagedPool, buflen, ALLOC_TAG);
    if (!fcb->sd) {
        ERR("out of memory\n");
        goto end;
    }

    Status = RtlAbsoluteToSelfRelativeSD(&sd, fcb->sd, &buflen);

    if (!NT_SUCCESS(Status)) {
        ERR("RtlAbsoluteToSelfRelativeSD 2 returned %08x\n", Status);
        ExFreePool(fcb->sd);
        fcb->sd = NULL;
        goto end;
    }

end:
    if (acl)
        ExFreePool(acl);

    if (usersid)
        ExFreePool(usersid);

    if (groupsid)
        ExFreePool(groupsid);
}