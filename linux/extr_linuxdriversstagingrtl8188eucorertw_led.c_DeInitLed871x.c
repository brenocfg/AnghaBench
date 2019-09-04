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
struct LED_871x {int /*<<< orphan*/  BlinkTimer; int /*<<< orphan*/  BlinkWorkItem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ResetLedStatus (struct LED_871x*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

void DeInitLed871x(struct LED_871x *pLed)
{
	cancel_work_sync(&pLed->BlinkWorkItem);
	del_timer_sync(&pLed->BlinkTimer);
	ResetLedStatus(pLed);
}