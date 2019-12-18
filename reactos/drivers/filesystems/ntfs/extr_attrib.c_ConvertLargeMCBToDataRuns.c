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
typedef  scalar_t__ ULONGLONG ;
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ UCHAR ;
typedef  scalar_t__* PULONG ;
typedef  scalar_t__* PUCHAR ;
typedef  int /*<<< orphan*/  PLARGE_MCB ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ LONGLONG ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ FsRtlGetNextLargeMcbEntry (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ GetPackedByteCount (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 

NTSTATUS
ConvertLargeMCBToDataRuns(PLARGE_MCB DataRunsMCB,
                          PUCHAR RunBuffer,
                          ULONG MaxBufferSize,
                          PULONG UsedBufferSize)
{
    NTSTATUS Status = STATUS_SUCCESS;
    ULONG RunBufferOffset = 0;
    LONGLONG  DataRunOffset;
    ULONGLONG LastLCN = 0;
    LONGLONG Vbn, Lbn, Count;
    ULONG i;


    DPRINT("\t[Vbn, Lbn, Count]\n");

    // convert each mcb entry to a data run
    for (i = 0; FsRtlGetNextLargeMcbEntry(DataRunsMCB, i, &Vbn, &Lbn, &Count); i++)
    {
        UCHAR DataRunOffsetSize = 0;
        UCHAR DataRunLengthSize = 0;
        UCHAR ControlByte = 0;

        // [vbn, lbn, count]
        DPRINT("\t[%I64d, %I64d,%I64d]\n", Vbn, Lbn, Count);

        // TODO: check for holes and convert to sparse runs
        DataRunOffset = Lbn - LastLCN;
        LastLCN = Lbn;

        // now we need to determine how to represent DataRunOffset with the minimum number of bytes
        DPRINT("Determining how many bytes needed to represent %I64x\n", DataRunOffset);
        DataRunOffsetSize = GetPackedByteCount(DataRunOffset, TRUE);
        DPRINT("%d bytes needed.\n", DataRunOffsetSize);

        // determine how to represent DataRunLengthSize with the minimum number of bytes
        DPRINT("Determining how many bytes needed to represent %I64x\n", Count);
        DataRunLengthSize = GetPackedByteCount(Count, TRUE);
        DPRINT("%d bytes needed.\n", DataRunLengthSize);

        // ensure the next data run + end marker would be <= Max buffer size
        if (RunBufferOffset + 2 + DataRunLengthSize + DataRunOffsetSize > MaxBufferSize)
        {
            Status = STATUS_BUFFER_TOO_SMALL;
            DPRINT1("FIXME: Ran out of room in buffer for data runs!\n");
            break;
        }

        // pack and copy the control byte
        ControlByte = (DataRunOffsetSize << 4) + DataRunLengthSize;
        RunBuffer[RunBufferOffset++] = ControlByte;

        // copy DataRunLength
        RtlCopyMemory(RunBuffer + RunBufferOffset, &Count, DataRunLengthSize);
        RunBufferOffset += DataRunLengthSize;

        // copy DataRunOffset
        RtlCopyMemory(RunBuffer + RunBufferOffset, &DataRunOffset, DataRunOffsetSize);
        RunBufferOffset += DataRunOffsetSize;
    }

    // End of data runs
    RunBuffer[RunBufferOffset++] = 0;

    *UsedBufferSize = RunBufferOffset;
    DPRINT("New Size of DataRuns: %ld\n", *UsedBufferSize);

    return Status;
}