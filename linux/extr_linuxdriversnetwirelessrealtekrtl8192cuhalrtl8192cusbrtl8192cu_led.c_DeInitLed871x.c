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
struct TYPE_4__ {int /*<<< orphan*/  BlinkTimer; int /*<<< orphan*/  BlinkWorkItem; } ;
typedef  TYPE_1__* PLED_871x ;

/* Variables and functions */
 int /*<<< orphan*/  ResetLedStatus (TYPE_1__*) ; 
 int /*<<< orphan*/  _cancel_timer_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cancel_workitem_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
DeInitLed871x(
	PLED_871x			pLed
	)
{
	//call _cancel_workitem_sync(&(pLed->BlinkWorkItem)) 
    //before _cancel_timer_ex(&(pLed->BlinkTimer)) to 
    //avoid led timer restarting when driver is removed

	_cancel_workitem_sync(&(pLed->BlinkWorkItem));
	
	_cancel_timer_ex(&(pLed->BlinkTimer));
	
	// We should reset bLedBlinkInProgress if we cancel the LedControlTimer, 2005.03.10, by rcnjko.
	ResetLedStatus(pLed);
}