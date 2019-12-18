#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UCHAR ;
struct TYPE_4__ {size_t tableSize; TYPE_1__* table; int /*<<< orphan*/  enumerated; } ;
struct TYPE_3__ {scalar_t__ transport; } ;

/* Variables and functions */
 TYPE_2__ gNBTable ; 
 int /*<<< orphan*/  nbInternalEnum () ; 

UCHAR NetBIOSNumAdapters(void)
{
    UCHAR ret, i;

    if (!gNBTable.enumerated)
        nbInternalEnum();
    for (i = 0, ret = 0; i < gNBTable.tableSize; i++)
        if (gNBTable.table[i].transport != 0)
            ret++;
    return ret;
}