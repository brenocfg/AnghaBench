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
typedef  int /*<<< orphan*/  USHORT ;
typedef  size_t ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_8__ {size_t BytesPerSector; } ;
struct TYPE_11__ {TYPE_1__ NtfsInfo; } ;
struct TYPE_10__ {int /*<<< orphan*/  USN; int /*<<< orphan*/ * Array; } ;
struct TYPE_9__ {size_t UsaCount; int UsaOffset; } ;
typedef  TYPE_2__* PNTFS_RECORD_HEADER ;
typedef  TYPE_3__* PFIXUP_ARRAY ;
typedef  TYPE_4__* PDEVICE_EXTENSION ;
typedef  int PCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,TYPE_4__*,...) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
AddFixupArray(PDEVICE_EXTENSION Vcb,
              PNTFS_RECORD_HEADER Record)
{
    USHORT *pShortToFixUp;
    ULONG ArrayEntryCount = Record->UsaCount - 1;
    ULONG Offset = Vcb->NtfsInfo.BytesPerSector - 2;
    ULONG i;

    PFIXUP_ARRAY fixupArray = (PFIXUP_ARRAY)((UCHAR*)Record + Record->UsaOffset);

    DPRINT("AddFixupArray(%p, %p)\n fixupArray->USN: %u, ArrayEntryCount: %u\n", Vcb, Record, fixupArray->USN, ArrayEntryCount);

    fixupArray->USN++;

    for (i = 0; i < ArrayEntryCount; i++)
    {
        DPRINT("USN: %u\tOffset: %u\n", fixupArray->USN, Offset);

        pShortToFixUp = (USHORT*)((PCHAR)Record + Offset);
        fixupArray->Array[i] = *pShortToFixUp;
        *pShortToFixUp = fixupArray->USN;
        Offset += Vcb->NtfsInfo.BytesPerSector;
    }

    return STATUS_SUCCESS;
}