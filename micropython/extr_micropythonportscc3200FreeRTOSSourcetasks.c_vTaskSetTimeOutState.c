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
struct TYPE_4__ {int /*<<< orphan*/  xTimeOnEntering; int /*<<< orphan*/  xOverflowCount; } ;
typedef  TYPE_1__ TimeOut_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (TYPE_1__* const) ; 
 int /*<<< orphan*/  xNumOfOverflows ; 
 int /*<<< orphan*/  xTickCount ; 

void vTaskSetTimeOutState( TimeOut_t * const pxTimeOut )
{
	configASSERT( pxTimeOut );
	pxTimeOut->xOverflowCount = xNumOfOverflows;
	pxTimeOut->xTimeOnEntering = xTickCount;
}