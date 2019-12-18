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
typedef  int /*<<< orphan*/  VOID ;

/* Variables and functions */
 int /*<<< orphan*/  MmuDbgInit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MmuInit () ; 
 int /*<<< orphan*/  MmuSetMemorySize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_range_end ; 
 int mmu_initialized ; 

VOID PpcInitializeMmu()
{
    if(!mmu_initialized)
    {
    MmuInit();
    MmuDbgInit(0, 0x800003f8);
        MmuSetMemorySize(mem_range_end);
        //MmuDbgEnter(0x20);
    mmu_initialized = 1;
    }
}