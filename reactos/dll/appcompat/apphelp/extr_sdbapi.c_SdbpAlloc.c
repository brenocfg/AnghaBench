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
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SdbpHeap () ; 
 int /*<<< orphan*/  SdbpInsertAllocation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*) ; 

LPVOID SdbpAlloc(SIZE_T size
#if SDBAPI_DEBUG_ALLOC
    , int line, const char* file
#endif
    )
{
    LPVOID mem = RtlAllocateHeap(SdbpHeap(), HEAP_ZERO_MEMORY, size);
#if SDBAPI_DEBUG_ALLOC
    SdbpInsertAllocation(mem, size, line, file);
#endif
    return mem;
}