#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {struct TYPE_3__* NextKey; } ;
typedef  TYPE_1__* PB_TREE_KEY ;

/* Variables and functions */

ULONG
CountBTreeKeys(PB_TREE_KEY FirstKey)
{
    ULONG Count = 0;
    PB_TREE_KEY Current = FirstKey;
    
    while (Current != NULL)
    {
        Count++;
        Current = Current->NextKey;
    }

    return Count;
}