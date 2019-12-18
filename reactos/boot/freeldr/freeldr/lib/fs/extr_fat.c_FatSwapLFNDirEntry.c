#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {void** Name11_12; void** Name5_10; void** Name0_4; } ;
typedef  TYPE_1__* PLFN_DIRENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  SW (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* SWAPW (void*) ; 
 int /*<<< orphan*/  StartCluster ; 

VOID FatSwapLFNDirEntry(PLFN_DIRENTRY Obj)
{
    int i;
    SW(Obj, StartCluster);
    for(i = 0; i < 5; i++)
        Obj->Name0_4[i] = SWAPW(Obj->Name0_4[i]);
    for(i = 0; i < 6; i++)
        Obj->Name5_10[i] = SWAPW(Obj->Name5_10[i]);
    for(i = 0; i < 2; i++)
        Obj->Name11_12[i] = SWAPW(Obj->Name11_12[i]);
}