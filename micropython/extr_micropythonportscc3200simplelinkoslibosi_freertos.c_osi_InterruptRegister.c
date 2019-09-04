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
typedef  scalar_t__ P_OSI_INTR_ENTRY ;
typedef  int /*<<< orphan*/  OsiReturnVal_e ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_IntEnable (int) ; 
 int /*<<< orphan*/  MAP_IntPrioritySet (int,unsigned char) ; 
 int /*<<< orphan*/  MAP_IntRegister (int,void (*) ()) ; 
 int /*<<< orphan*/  OSI_OK ; 

OsiReturnVal_e osi_InterruptRegister(int iIntrNum,P_OSI_INTR_ENTRY pEntry,unsigned char ucPriority)
{
	MAP_IntRegister(iIntrNum,(void(*)(void))pEntry);
	MAP_IntPrioritySet(iIntrNum, ucPriority);
	MAP_IntEnable(iIntrNum);
	return OSI_OK;
}