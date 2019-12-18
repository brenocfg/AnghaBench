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
typedef  scalar_t__ OsiLockObj_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSI_OK ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ ) ; 

OsiReturnVal_e _osi_LockObjDelete(OsiLockObj_t* pLockObj)
{
    vSemaphoreDelete((SemaphoreHandle_t)*pLockObj );
    return OSI_OK;
}