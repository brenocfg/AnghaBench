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
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_12__ {int elements; } ;
struct TYPE_11__ {TYPE_6__* sid; int /*<<< orphan*/  mask; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int AceSize; int /*<<< orphan*/  AceFlags; int /*<<< orphan*/  AceType; } ;
struct TYPE_10__ {TYPE_1__ Header; int /*<<< orphan*/  SidStart; int /*<<< orphan*/  Mask; } ;
struct TYPE_9__ {size_t AclSize; size_t AceCount; scalar_t__ Sbz2; scalar_t__ Sbz1; int /*<<< orphan*/  AclRevision; } ;
typedef  TYPE_2__ ACL ;
typedef  TYPE_3__ ACCESS_ALLOWED_ACE ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_ALLOWED_ACE_TYPE ; 
 int /*<<< orphan*/  ACL_REVISION ; 
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*) ; 
 TYPE_2__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,TYPE_6__*,int) ; 
 TYPE_5__* def_dacls ; 

__attribute__((used)) static ACL* load_default_acl() {
    uint16_t size, i;
    ACL* acl;
    ACCESS_ALLOWED_ACE* aaa;

    size = sizeof(ACL);
    i = 0;
    while (def_dacls[i].sid) {
        size += sizeof(ACCESS_ALLOWED_ACE);
        size += 8 + (def_dacls[i].sid->elements * sizeof(uint32_t)) - sizeof(ULONG);
        i++;
    }

    acl = ExAllocatePoolWithTag(PagedPool, size, ALLOC_TAG);
    if (!acl) {
        ERR("out of memory\n");
        return NULL;
    }

    acl->AclRevision = ACL_REVISION;
    acl->Sbz1 = 0;
    acl->AclSize = size;
    acl->AceCount = i;
    acl->Sbz2 = 0;

    aaa = (ACCESS_ALLOWED_ACE*)&acl[1];
    i = 0;
    while (def_dacls[i].sid) {
        aaa->Header.AceType = ACCESS_ALLOWED_ACE_TYPE;
        aaa->Header.AceFlags = def_dacls[i].flags;
        aaa->Header.AceSize = sizeof(ACCESS_ALLOWED_ACE) - sizeof(ULONG) + 8 + (def_dacls[i].sid->elements * sizeof(uint32_t));
        aaa->Mask = def_dacls[i].mask;

        RtlCopyMemory(&aaa->SidStart, def_dacls[i].sid, 8 + (def_dacls[i].sid->elements * sizeof(uint32_t)));

        aaa = (ACCESS_ALLOWED_ACE*)((uint8_t*)aaa + aaa->Header.AceSize);

        i++;
    }

    return acl;
}