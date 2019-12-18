#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_9__ {TYPE_4__* Flink; } ;
struct TYPE_13__ {TYPE_1__ ListEntry; int /*<<< orphan*/  Signature; int /*<<< orphan*/  CheckSum; int /*<<< orphan*/  ArcName; } ;
struct TYPE_12__ {struct TYPE_12__* Flink; } ;
struct TYPE_11__ {TYPE_2__* ArcDiskInformation; } ;
struct TYPE_10__ {TYPE_4__ DiskSignatureListHead; } ;
typedef  TYPE_3__* PLOADER_PARAMETER_BLOCK ;
typedef  TYPE_4__* PLIST_ENTRY ;
typedef  TYPE_5__* PARC_DISK_SIGNATURE ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_DISK_SIGNATURE ; 
 TYPE_5__* CONTAINING_RECORD (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID
WinLdrpDumpArcDisks(PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    PLIST_ENTRY NextBd;
    PARC_DISK_SIGNATURE ArcDisk;

    NextBd = LoaderBlock->ArcDiskInformation->DiskSignatureListHead.Flink;

    while (NextBd != &LoaderBlock->ArcDiskInformation->DiskSignatureListHead)
    {
        ArcDisk = CONTAINING_RECORD(NextBd, ARC_DISK_SIGNATURE, ListEntry);

        TRACE("ArcDisk %s checksum: 0x%X, signature: 0x%X\n",
            ArcDisk->ArcName, ArcDisk->CheckSum, ArcDisk->Signature);

        NextBd = ArcDisk->ListEntry.Flink;
    }
}