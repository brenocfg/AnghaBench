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
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PFREELDR_MEMORY_DESCRIPTOR ;

/* Variables and functions */
 int AvailableMemoryMb ; 
 scalar_t__ FrameBuffer ; 
 scalar_t__ FrameBufferSize ; 
 int /*<<< orphan*/  LoaderFirmwarePermanent ; 
 int /*<<< orphan*/  LoaderFree ; 
 int /*<<< orphan*/  PcMemFinalizeMemoryMap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReserveMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SetMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  XboxMemoryMap ; 

PFREELDR_MEMORY_DESCRIPTOR
XboxMemGetMemoryMap(ULONG *MemoryMapSize)
{
    TRACE("XboxMemGetMemoryMap()\n");
    /* FIXME: Obtain memory map via multiboot spec */

    /* Synthesize memory map */

    /* Available RAM block */
    SetMemory(XboxMemoryMap,
              0,
              AvailableMemoryMb * 1024 * 1024,
              LoaderFree);

    if (FrameBufferSize != 0)
    {
        /* Video memory */
        ReserveMemory(XboxMemoryMap,
                      (ULONG_PTR)FrameBuffer,
                      FrameBufferSize,
                      LoaderFirmwarePermanent,
                      "Video memory");
    }

    *MemoryMapSize = PcMemFinalizeMemoryMap(XboxMemoryMap);
    return XboxMemoryMap;
}