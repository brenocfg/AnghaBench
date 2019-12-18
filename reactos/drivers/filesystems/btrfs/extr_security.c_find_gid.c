#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int st_mode; int /*<<< orphan*/  st_gid; } ;
struct _fcb {TYPE_1__ inode_item; } ;
typedef  size_t ULONG ;
struct TYPE_12__ {int /*<<< orphan*/  PrimaryToken; } ;
struct TYPE_11__ {size_t GroupCount; TYPE_2__* Groups; int /*<<< orphan*/  PrimaryGroup; int /*<<< orphan*/  Owner; } ;
struct TYPE_10__ {int /*<<< orphan*/  Sid; } ;
typedef  TYPE_3__ TOKEN_PRIMARY_GROUP ;
typedef  TYPE_3__ TOKEN_OWNER ;
typedef  TYPE_3__ TOKEN_GROUPS ;
typedef  TYPE_6__* PSECURITY_SUBJECT_CONTEXT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExAcquireResourceSharedLite (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_3__*) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 scalar_t__ IsListEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int S_ISGID ; 
 int /*<<< orphan*/  SeQueryInformationToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  TokenGroups ; 
 int /*<<< orphan*/  TokenOwner ; 
 int /*<<< orphan*/  TokenPrimaryGroup ; 
 int /*<<< orphan*/  gid_map_list ; 
 int /*<<< orphan*/  mapping_lock ; 
 scalar_t__ search_for_gid (struct _fcb*,int /*<<< orphan*/ ) ; 

void find_gid(struct _fcb* fcb, struct _fcb* parfcb, PSECURITY_SUBJECT_CONTEXT subjcont) {
    NTSTATUS Status;
    TOKEN_OWNER* to;
    TOKEN_PRIMARY_GROUP* tpg;
    TOKEN_GROUPS* tg;

    if (parfcb && parfcb->inode_item.st_mode & S_ISGID) {
        fcb->inode_item.st_gid = parfcb->inode_item.st_gid;
        return;
    }

    ExAcquireResourceSharedLite(&mapping_lock, true);

    if (!subjcont || !subjcont->PrimaryToken || IsListEmpty(&gid_map_list)) {
        ExReleaseResourceLite(&mapping_lock);
        return;
    }

    Status = SeQueryInformationToken(subjcont->PrimaryToken, TokenOwner, (void**)&to);
    if (!NT_SUCCESS(Status))
        ERR("SeQueryInformationToken returned %08x\n", Status);
    else {
        if (search_for_gid(fcb, to->Owner)) {
            ExReleaseResourceLite(&mapping_lock);
            ExFreePool(to);
            return;
        }

        ExFreePool(to);
    }

    Status = SeQueryInformationToken(subjcont->PrimaryToken, TokenPrimaryGroup, (void**)&tpg);
    if (!NT_SUCCESS(Status))
        ERR("SeQueryInformationToken returned %08x\n", Status);
    else {
        if (search_for_gid(fcb, tpg->PrimaryGroup)) {
            ExReleaseResourceLite(&mapping_lock);
            ExFreePool(tpg);
            return;
        }

        ExFreePool(tpg);
    }

    Status = SeQueryInformationToken(subjcont->PrimaryToken, TokenGroups, (void**)&tg);
    if (!NT_SUCCESS(Status))
        ERR("SeQueryInformationToken returned %08x\n", Status);
    else {
        ULONG i;

        for (i = 0; i < tg->GroupCount; i++) {
            if (search_for_gid(fcb, tg->Groups[i].Sid)) {
                ExReleaseResourceLite(&mapping_lock);
                ExFreePool(tg);
                return;
            }
        }

        ExFreePool(tg);
    }

    ExReleaseResourceLite(&mapping_lock);
}