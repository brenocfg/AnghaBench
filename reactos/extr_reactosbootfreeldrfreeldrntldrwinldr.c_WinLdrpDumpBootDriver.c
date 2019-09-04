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
struct TYPE_8__ {TYPE_3__* Flink; } ;
struct TYPE_11__ {TYPE_1__ Link; int /*<<< orphan*/  RegistryPath; int /*<<< orphan*/  LdrEntry; int /*<<< orphan*/  FilePath; } ;
struct TYPE_10__ {struct TYPE_10__* Flink; } ;
struct TYPE_9__ {TYPE_3__ BootDriverListHead; } ;
typedef  TYPE_2__* PLOADER_PARAMETER_BLOCK ;
typedef  TYPE_3__* PLIST_ENTRY ;
typedef  TYPE_4__* PBOOT_DRIVER_LIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  BOOT_DRIVER_LIST_ENTRY ; 
 TYPE_4__* CONTAINING_RECORD (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Link ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

VOID
WinLdrpDumpBootDriver(PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    PLIST_ENTRY NextBd;
    PBOOT_DRIVER_LIST_ENTRY BootDriver;

    NextBd = LoaderBlock->BootDriverListHead.Flink;

    while (NextBd != &LoaderBlock->BootDriverListHead)
    {
        BootDriver = CONTAINING_RECORD(NextBd, BOOT_DRIVER_LIST_ENTRY, Link);

        TRACE("BootDriver %wZ DTE %08X RegPath: %wZ\n", &BootDriver->FilePath,
            BootDriver->LdrEntry, &BootDriver->RegistryPath);

        NextBd = BootDriver->Link.Flink;
    }
}