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
 int /*<<< orphan*/  RtlDestroyHeap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SdbpDebugHeapDeinit () ; 
 int /*<<< orphan*/  g_Heap ; 

void SdbpHeapDeinit(void)
{
#if SDBAPI_DEBUG_ALLOC
    SdbpDebugHeapDeinit();
#endif
    RtlDestroyHeap(g_Heap);
}