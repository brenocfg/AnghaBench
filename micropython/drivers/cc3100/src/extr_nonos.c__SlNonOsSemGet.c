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
typedef  scalar_t__ _SlNonOsTime_t ;
typedef  scalar_t__ _SlNonOsSemObj_t ;
typedef  int /*<<< orphan*/  _SlNonOsRetVal_t ;

/* Variables and functions */
 scalar_t__ NONOS_NO_WAIT ; 
 int /*<<< orphan*/  NONOS_RET_ERR ; 
 int /*<<< orphan*/  NONOS_RET_OK ; 
 scalar_t__ NONOS_WAIT_FOREVER ; 
 int /*<<< orphan*/  _SlNonOsMainLoopTask () ; 
 int /*<<< orphan*/  _SlSyncWaitLoopCallback () ; 
 scalar_t__ __NON_OS_SYNC_OBJ_SIGNAL_VALUE ; 

_SlNonOsRetVal_t _SlNonOsSemGet(_SlNonOsSemObj_t* pSyncObj, _SlNonOsSemObj_t WaitValue, _SlNonOsSemObj_t SetValue, _SlNonOsTime_t Timeout)
{
#ifdef _SlSyncWaitLoopCallback
    _SlNonOsTime_t timeOutRequest = Timeout; 
#endif
    while (Timeout>0)
    {
        if (WaitValue == *pSyncObj)
        {
            *pSyncObj = SetValue;
            break;
        }
        if (Timeout != NONOS_WAIT_FOREVER)
        {		
            Timeout--;
        }
        _SlNonOsMainLoopTask();
#ifdef _SlSyncWaitLoopCallback
        if( (__NON_OS_SYNC_OBJ_SIGNAL_VALUE == WaitValue) && (timeOutRequest != NONOS_NO_WAIT) )
        {
            if (WaitValue == *pSyncObj)
            {
                *pSyncObj = SetValue;
                break;
            }
            _SlSyncWaitLoopCallback();
        }
#endif
    }

    if (0 == Timeout)
    {
        return NONOS_RET_ERR;
    }
    else
    {
        return NONOS_RET_OK;
    }
}