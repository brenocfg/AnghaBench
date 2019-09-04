#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  BlinkingLedState; scalar_t__ BlinkTimes; void* bLedWPSBlinkInProgress; void* bLedScanBlinkInProgress; void* bLedStartToLinkBlinkInProgress; void* bLedLinkBlinkInProgress; void* bLedNoLinkBlinkInProgress; void* bLedBlinkInProgress; void* bLedOn; int /*<<< orphan*/  CurrLedState; } ;
typedef  TYPE_1__* PLED_871x ;

/* Variables and functions */
 int /*<<< orphan*/  LED_UNKNOWN ; 
 int /*<<< orphan*/  RTW_LED_OFF ; 
 void* _FALSE ; 

__attribute__((used)) static void
ResetLedStatus(PLED_871x	pLed) {
	pLed->CurrLedState = RTW_LED_OFF; // Current LED state.
	pLed->bLedOn = _FALSE; // true if LED is ON, false if LED is OFF.
	
	pLed->bLedBlinkInProgress = _FALSE; // true if it is blinking, false o.w..
	pLed->bLedNoLinkBlinkInProgress = _FALSE;
	pLed->bLedLinkBlinkInProgress = _FALSE;
	pLed->bLedStartToLinkBlinkInProgress = _FALSE;
	pLed->bLedScanBlinkInProgress = _FALSE;
	pLed->bLedWPSBlinkInProgress = _FALSE;
	pLed->BlinkTimes = 0; // Number of times to toggle led state for blinking.
	pLed->BlinkingLedState = LED_UNKNOWN; // Next state for blinking, either RTW_LED_ON or RTW_LED_OFF are.
}