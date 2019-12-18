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

/* Variables and functions */
 unsigned int* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (unsigned int*) ; 
 int /*<<< orphan*/  HIST_ALLOC_TAG ; 
 int HIST_WKSP_SIZE_U32 ; 
 size_t HIST_countFast_wksp (unsigned int*,unsigned int*,void const*,size_t,unsigned int*) ; 
 int /*<<< orphan*/  NonPagedPool ; 

size_t HIST_countFast(unsigned* count, unsigned* maxSymbolValuePtr,
                     const void* source, size_t sourceSize)
{
    unsigned* tmpCounters = ExAllocatePoolWithTag(NonPagedPool, sizeof(unsigned) * HIST_WKSP_SIZE_U32, HIST_ALLOC_TAG);
    size_t ret;

    if (!tmpCounters)
        return 0;

    ret = HIST_countFast_wksp(count, maxSymbolValuePtr, source, sourceSize, tmpCounters);

    ExFreePool(tmpCounters);

    return ret;
}