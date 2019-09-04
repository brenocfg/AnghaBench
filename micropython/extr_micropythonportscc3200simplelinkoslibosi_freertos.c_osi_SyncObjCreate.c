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
typedef  int /*<<< orphan*/ * OsiSyncObj_t ;
typedef  int /*<<< orphan*/  OsiReturnVal_e ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSI_OK ; 
 int /*<<< orphan*/  xSemaphoreCreateBinary () ; 

OsiReturnVal_e osi_SyncObjCreate(OsiSyncObj_t* pSyncObj)
{
    SemaphoreHandle_t *pl_SyncObj = (SemaphoreHandle_t *)pSyncObj;

    *pl_SyncObj = xSemaphoreCreateBinary();

    ASSERT (*pSyncObj != NULL);

    return OSI_OK;
}