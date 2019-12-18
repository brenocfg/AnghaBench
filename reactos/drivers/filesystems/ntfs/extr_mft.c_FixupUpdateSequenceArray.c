#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
struct TYPE_8__ {scalar_t__ BytesPerSector; } ;
struct TYPE_10__ {TYPE_1__ NtfsInfo; } ;
struct TYPE_9__ {scalar_t__ UsaCount; scalar_t__ UsaOffset; } ;
typedef  TYPE_2__* PNTFS_RECORD_HEADER ;
typedef  TYPE_3__* PDEVICE_EXTENSION ;
typedef  scalar_t__ PCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,TYPE_3__*,TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DPRINT1 (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 

NTSTATUS
FixupUpdateSequenceArray(PDEVICE_EXTENSION Vcb,
                         PNTFS_RECORD_HEADER Record)
{
    USHORT *USA;
    USHORT USANumber;
    USHORT USACount;
    USHORT *Block;

    USA = (USHORT*)((PCHAR)Record + Record->UsaOffset);
    USANumber = *(USA++);
    USACount = Record->UsaCount - 1; /* Exclude the USA Number. */
    Block = (USHORT*)((PCHAR)Record + Vcb->NtfsInfo.BytesPerSector - 2);

    DPRINT("FixupUpdateSequenceArray(%p, %p)\nUSANumber: %u\tUSACount: %u\n", Vcb, Record, USANumber, USACount);

    while (USACount)
    {
        if (*Block != USANumber)
        {
            DPRINT1("Mismatch with USA: %u read, %u expected\n" , *Block, USANumber);
            return STATUS_UNSUCCESSFUL;
        }
        *Block = *(USA++);
        Block = (USHORT*)((PCHAR)Block + Vcb->NtfsInfo.BytesPerSector);
        USACount--;
    }

    return STATUS_SUCCESS;
}