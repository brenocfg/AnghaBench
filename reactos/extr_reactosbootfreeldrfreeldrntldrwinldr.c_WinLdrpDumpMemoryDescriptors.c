#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_11__ {struct TYPE_11__* Flink; } ;
struct TYPE_10__ {TYPE_4__ MemoryDescriptorListHead; } ;
struct TYPE_8__ {TYPE_4__* Flink; } ;
struct TYPE_9__ {TYPE_1__ ListEntry; int /*<<< orphan*/  MemoryType; int /*<<< orphan*/  PageCount; int /*<<< orphan*/  BasePage; } ;
typedef  TYPE_2__* PMEMORY_ALLOCATION_DESCRIPTOR ;
typedef  TYPE_3__* PLOADER_PARAMETER_BLOCK ;
typedef  TYPE_4__* PLIST_ENTRY ;

/* Variables and functions */
 TYPE_2__* CONTAINING_RECORD (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  MEMORY_ALLOCATION_DESCRIPTOR ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID
WinLdrpDumpMemoryDescriptors(PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    PLIST_ENTRY NextMd;
    PMEMORY_ALLOCATION_DESCRIPTOR MemoryDescriptor;

    NextMd = LoaderBlock->MemoryDescriptorListHead.Flink;

    while (NextMd != &LoaderBlock->MemoryDescriptorListHead)
    {
        MemoryDescriptor = CONTAINING_RECORD(NextMd, MEMORY_ALLOCATION_DESCRIPTOR, ListEntry);

        TRACE("BP %08X PC %04X MT %d\n", MemoryDescriptor->BasePage,
            MemoryDescriptor->PageCount, MemoryDescriptor->MemoryType);

        NextMd = MemoryDescriptor->ListEntry.Flink;
    }
}