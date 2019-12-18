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
 size_t HIST_count_parallel_wksp (unsigned int*,unsigned int*,void const*,size_t,int /*<<< orphan*/ ,unsigned int*) ; 
 size_t HIST_count_simple (unsigned int*,unsigned int*,void const*,size_t) ; 

size_t HIST_countFast_wksp(unsigned* count, unsigned* maxSymbolValuePtr,
                          const void* source, size_t sourceSize,
                          unsigned* workSpace)
{
    if (sourceSize < 1500) /* heuristic threshold */
        return HIST_count_simple(count, maxSymbolValuePtr, source, sourceSize);
    return HIST_count_parallel_wksp(count, maxSymbolValuePtr, source, sourceSize, 0, workSpace);
}