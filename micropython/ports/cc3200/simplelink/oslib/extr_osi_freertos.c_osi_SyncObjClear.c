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
typedef  int /*<<< orphan*/  OsiSyncObj_t ;
typedef  scalar_t__ OsiReturnVal_e ;

/* Variables and functions */
 scalar_t__ OSI_OK ; 
 scalar_t__ OSI_OPERATION_FAILED ; 
 scalar_t__ osi_SyncObjWait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

OsiReturnVal_e osi_SyncObjClear(OsiSyncObj_t* pSyncObj)
{
    if (OSI_OK == osi_SyncObjWait(pSyncObj,0) )
    {
        return OSI_OK;
    }
    else
    {
        return OSI_OPERATION_FAILED;
    }
}