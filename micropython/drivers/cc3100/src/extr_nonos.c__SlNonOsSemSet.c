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
typedef  int /*<<< orphan*/  _SlNonOsSemObj_t ;
typedef  int /*<<< orphan*/  _SlNonOsRetVal_t ;

/* Variables and functions */
 int /*<<< orphan*/  NONOS_RET_OK ; 

_SlNonOsRetVal_t _SlNonOsSemSet(_SlNonOsSemObj_t* pSemObj , _SlNonOsSemObj_t Value)
{
    *pSemObj = Value;
    return NONOS_RET_OK;
}