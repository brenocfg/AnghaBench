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
typedef  int /*<<< orphan*/  OsiReturnVal_e ;
typedef  int /*<<< orphan*/  OsiLockObj_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSI_OK ; 
 int /*<<< orphan*/  OSI_OPERATION_FAILED ; 
 scalar_t__ pdTRUE ; 
 scalar_t__ xSemaphoreGive (int /*<<< orphan*/ ) ; 

OsiReturnVal_e _osi_LockObjUnlock(OsiLockObj_t* pLockObj)
{
	//Release Semaphore
    if(pdTRUE == xSemaphoreGive( *pLockObj ))
    {
    	return OSI_OK;
    }
    else
    {
    	return OSI_OPERATION_FAILED;
    }
}