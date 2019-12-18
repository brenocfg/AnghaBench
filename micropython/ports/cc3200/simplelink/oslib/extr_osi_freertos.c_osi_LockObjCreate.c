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
typedef  int /*<<< orphan*/  SemaphoreHandle_t ;
typedef  int /*<<< orphan*/  OsiReturnVal_e ;
typedef  int /*<<< orphan*/ * OsiLockObj_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSI_OK ; 
 int /*<<< orphan*/  vSemaphoreCreateBinary (int /*<<< orphan*/ ) ; 

OsiReturnVal_e osi_LockObjCreate(OsiLockObj_t* pLockObj)
{
    SemaphoreHandle_t *pl_LockObj = (SemaphoreHandle_t *)pLockObj;

    vSemaphoreCreateBinary(*pl_LockObj);

    ASSERT (*pLockObj != NULL);

    return OSI_OK;
}