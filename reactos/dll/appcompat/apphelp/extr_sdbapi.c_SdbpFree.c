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
typedef  int /*<<< orphan*/  LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SdbpHeap () ; 
 int /*<<< orphan*/  SdbpRemoveAllocation (int /*<<< orphan*/ ,int,char const*) ; 

void SdbpFree(LPVOID mem
#if SDBAPI_DEBUG_ALLOC
    , int line, const char* file
#endif
    )
{
#if SDBAPI_DEBUG_ALLOC
    SdbpRemoveAllocation(mem, line, file);
#endif
    RtlFreeHeap(SdbpHeap(), 0, mem);
}