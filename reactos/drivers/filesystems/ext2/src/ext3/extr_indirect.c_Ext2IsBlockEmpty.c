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
typedef  size_t ULONG ;
typedef  scalar_t__* PULONG ;
typedef  int BOOLEAN ;

/* Variables and functions */

BOOLEAN
Ext2IsBlockEmpty(PULONG BlockArray, ULONG SizeArray)
{
    ULONG i = 0;
    for (i=0; i < SizeArray; i++) {
        if (BlockArray[i]) {
            break;
        }
    }
    return (i == SizeArray);
}