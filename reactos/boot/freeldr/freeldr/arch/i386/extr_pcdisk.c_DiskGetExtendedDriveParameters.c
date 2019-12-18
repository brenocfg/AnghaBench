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
typedef  int USHORT ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_10__ {int /*<<< orphan*/  si; } ;
struct TYPE_9__ {int /*<<< orphan*/  ds; } ;
struct TYPE_8__ {int ah; int /*<<< orphan*/  dl; } ;
struct TYPE_11__ {TYPE_3__ w; TYPE_2__ x; TYPE_1__ b; } ;
typedef  TYPE_4__ REGS ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int* PUSHORT ;
typedef  int* PULONG ;
typedef  int* PUCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ BIOSCALLBUFFER ; 
 int /*<<< orphan*/  BIOSCALLBUFOFFSET ; 
 int /*<<< orphan*/  BIOSCALLBUFSEGMENT ; 
 int /*<<< orphan*/  DiskInt13ExtensionsSupported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INT386_SUCCESS (TYPE_4__) ; 
 int /*<<< orphan*/  Int386 (int,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

BOOLEAN DiskGetExtendedDriveParameters(UCHAR DriveNumber, PVOID Buffer, USHORT BufferSize)
{
    REGS RegsIn, RegsOut;
    PUSHORT Ptr = (PUSHORT)(BIOSCALLBUFFER);

    TRACE("DiskGetExtendedDriveParameters()\n");

    if (!DiskInt13ExtensionsSupported(DriveNumber))
        return FALSE;

    /* Initialize transfer buffer */
    *Ptr = BufferSize;

    /*
     * BIOS Int 13h, function 48h - Get drive parameters
     * AH = 48h
     * DL = drive (bit 7 set for hard disk)
     * DS:SI = result buffer
     * Return:
     * CF set on error
     * AH = status (07h)
     * CF clear if successful
     * AH = 00h
     * DS:SI -> result buffer
     */
    RegsIn.b.ah = 0x48;
    RegsIn.b.dl = DriveNumber;
    RegsIn.x.ds = BIOSCALLBUFSEGMENT;   // DS:SI -> result buffer
    RegsIn.w.si = BIOSCALLBUFOFFSET;

    /* Get drive parameters */
    Int386(0x13, &RegsIn, &RegsOut);
    if (!INT386_SUCCESS(RegsOut))
        return FALSE;

    memcpy(Buffer, Ptr, BufferSize);

#if DBG
    TRACE("size of buffer:                          %x\n", Ptr[0]);
    TRACE("information flags:                       %x\n", Ptr[1]);
    TRACE("number of physical cylinders on drive:   %u\n", *(PULONG)&Ptr[2]);
    TRACE("number of physical heads on drive:       %u\n", *(PULONG)&Ptr[4]);
    TRACE("number of physical sectors per track:    %u\n", *(PULONG)&Ptr[6]);
    TRACE("total number of sectors on drive:        %I64u\n", *(unsigned long long*)&Ptr[8]);
    TRACE("bytes per sector:                        %u\n", Ptr[12]);
    if (Ptr[0] >= 0x1e)
    {
        TRACE("EED configuration parameters:            %x:%x\n", Ptr[13], Ptr[14]);
        if (Ptr[13] != 0xffff && Ptr[14] != 0xffff)
        {
           PUCHAR SpecPtr = (PUCHAR)(ULONG_PTR)((Ptr[13] << 4) + Ptr[14]);
           TRACE("SpecPtr:                                 %x\n", SpecPtr);
           TRACE("physical I/O port base address:          %x\n", *(PUSHORT)&SpecPtr[0]);
           TRACE("disk-drive control port address:         %x\n", *(PUSHORT)&SpecPtr[2]);
           TRACE("drive flags:                             %x\n", SpecPtr[4]);
           TRACE("proprietary information:                 %x\n", SpecPtr[5]);
           TRACE("IRQ for drive:                           %u\n", SpecPtr[6]);
           TRACE("sector count for multi-sector transfers: %u\n", SpecPtr[7]);
           TRACE("DMA control:                             %x\n", SpecPtr[8]);
           TRACE("programmed I/O control:                  %x\n", SpecPtr[9]);
           TRACE("drive options:                           %x\n", *(PUSHORT)&SpecPtr[10]);
        }
    }
    if (Ptr[0] >= 0x42)
    {
        TRACE("signature:                             %x\n", Ptr[15]);
    }
#endif

    return TRUE;
}