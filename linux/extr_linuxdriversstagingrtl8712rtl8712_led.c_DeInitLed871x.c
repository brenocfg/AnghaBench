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
struct LED_871x {int bLedBlinkInProgress; int /*<<< orphan*/  BlinkTimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DeInitLed871x(struct LED_871x *pLed)
{
	del_timer_sync(&pLed->BlinkTimer);
	/* We should reset bLedBlinkInProgress if we cancel
	 * the LedControlTimer,
	 */
	pLed->bLedBlinkInProgress = false;
}