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
typedef  int /*<<< orphan*/  superblock ;
struct TYPE_4__ {scalar_t__ num_bytes; } ;
struct TYPE_5__ {int /*<<< orphan*/  fileobj; int /*<<< orphan*/  devobj; TYPE_1__ devitem; } ;
typedef  TYPE_2__ device ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__* superblock_addrs ; 
 int /*<<< orphan*/  write_data_phys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static NTSTATUS remove_superblocks(device* dev) {
    NTSTATUS Status;
    superblock* sb;
    int i = 0;

    sb = ExAllocatePoolWithTag(PagedPool, sizeof(superblock), ALLOC_TAG);
    if (!sb) {
        ERR("out of memory\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    RtlZeroMemory(sb, sizeof(superblock));

    while (superblock_addrs[i] > 0 && dev->devitem.num_bytes >= superblock_addrs[i] + sizeof(superblock)) {
        Status = write_data_phys(dev->devobj, dev->fileobj, superblock_addrs[i], sb, sizeof(superblock));

        if (!NT_SUCCESS(Status)) {
            ExFreePool(sb);
            return Status;
        }

        i++;
    }

    ExFreePool(sb);

    return STATUS_SUCCESS;
}