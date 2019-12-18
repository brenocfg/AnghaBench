#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ PageCount; } ;
typedef  TYPE_1__ FREELDR_MEMORY_DESCRIPTOR ;

/* Variables and functions */
 TYPE_1__ const* BiosMemoryMap ; 

const FREELDR_MEMORY_DESCRIPTOR*
ArcGetMemoryDescriptor(const FREELDR_MEMORY_DESCRIPTOR* Current)
{
    if (Current == NULL)
    {
        return BiosMemoryMap;
    }
    else
    {
        Current++;
        if (Current->PageCount == 0) return NULL;
        return Current;
    }
}