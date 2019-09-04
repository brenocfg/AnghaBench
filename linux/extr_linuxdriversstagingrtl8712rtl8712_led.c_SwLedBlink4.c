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
typedef  int u8 ;
struct LED_871x {scalar_t__ BlinkingLedState; int CurrLedState; int BlinkTimes; int bLedNoLinkBlinkInProgress; int bLedScanBlinkInProgress; int bLedBlinkInProgress; int /*<<< orphan*/  BlinkTimer; int /*<<< orphan*/  bLedOn; int /*<<< orphan*/  bLedWPSBlinkInProgress; struct _adapter* padapter; } ;
struct led_priv {struct LED_871x SwLed1; } ;
struct _adapter {struct led_priv ledpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_BLINK_FASTER_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_LINK_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_NORMAL_INTERVAL ; 
 int /*<<< orphan*/  LED_BLINK_NO_LINK_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_SCAN_INTERVAL_ALPHA ; 
#define  LED_BLINK_SLOWLY 134 
 int /*<<< orphan*/  LED_BLINK_SLOWLY_INTERVAL ; 
#define  LED_BLINK_StartToBlink 133 
#define  LED_BLINK_WPS 132 
#define  LED_BLINK_WPS_STOP 131 
#define  LED_BLINK_WPS_STOP_OVERLAP 130 
#define  LED_SCAN_BLINK 129 
 void* LED_STATE_OFF ; 
 scalar_t__ LED_STATE_ON ; 
#define  LED_TXRX_BLINK 128 
 scalar_t__ LED_UNKNOWN ; 
 int /*<<< orphan*/  SwLedOff (struct _adapter*,struct LED_871x*) ; 
 int /*<<< orphan*/  SwLedOn (struct _adapter*,struct LED_871x*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SwLedBlink4(struct LED_871x *pLed)
{
	struct _adapter *padapter = pLed->padapter;
	struct led_priv	*ledpriv = &padapter->ledpriv;
	struct LED_871x *pLed1 = &ledpriv->SwLed1;
	u8 bStopBlinking = false;

	/* Change LED according to BlinkingLedState specified. */
	if (pLed->BlinkingLedState == LED_STATE_ON)
		SwLedOn(padapter, pLed);
	else
		SwLedOff(padapter, pLed);
	if (!pLed1->bLedWPSBlinkInProgress &&
	    pLed1->BlinkingLedState == LED_UNKNOWN) {
		pLed1->BlinkingLedState = LED_STATE_OFF;
		pLed1->CurrLedState = LED_STATE_OFF;
		SwLedOff(padapter, pLed1);
	}
	switch (pLed->CurrLedState) {
	case LED_BLINK_SLOWLY:
		if (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		else
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_timer(&pLed->BlinkTimer, jiffies +
			  msecs_to_jiffies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
		break;
	case LED_BLINK_StartToBlink:
		if (pLed->bLedOn) {
			pLed->BlinkingLedState = LED_STATE_OFF;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_SLOWLY_INTERVAL));
		} else {
			pLed->BlinkingLedState = LED_STATE_ON;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_NORMAL_INTERVAL));
		}
		break;
	case LED_SCAN_BLINK:
		pLed->BlinkTimes--;
		if (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		if (bStopBlinking) {
			pLed->bLedNoLinkBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_SLOWLY;
			if (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			else
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
			pLed->bLedScanBlinkInProgress = false;
		} else {
			if (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			else
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		}
		break;
	case LED_TXRX_BLINK:
		pLed->BlinkTimes--;
		if (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		if (bStopBlinking) {
			pLed->bLedNoLinkBlinkInProgress = true;
			pLed->CurrLedState = LED_BLINK_SLOWLY;
			if (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			else
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_NO_LINK_INTERVAL_ALPHA));
			pLed->bLedBlinkInProgress = false;
		} else {
			if (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			else
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_FASTER_INTERVAL_ALPHA));
		}
		break;
	case LED_BLINK_WPS:
		if (pLed->bLedOn) {
			pLed->BlinkingLedState = LED_STATE_OFF;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_SLOWLY_INTERVAL));
		} else {
			pLed->BlinkingLedState = LED_STATE_ON;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_NORMAL_INTERVAL));
		}
		break;
	case LED_BLINK_WPS_STOP:	/*WPS authentication fail*/
		if (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		else
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_timer(&pLed->BlinkTimer, jiffies +
			  msecs_to_jiffies(LED_BLINK_NORMAL_INTERVAL));
		break;
	case LED_BLINK_WPS_STOP_OVERLAP:	/*WPS session overlap */
		pLed->BlinkTimes--;
		if (pLed->BlinkTimes == 0) {
			if (pLed->bLedOn)
				pLed->BlinkTimes = 1;
			else
				bStopBlinking = true;
		}
		if (bStopBlinking) {
			pLed->BlinkTimes = 10;
			pLed->BlinkingLedState = LED_STATE_ON;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_LINK_INTERVAL_ALPHA));
		} else {
			if (pLed->bLedOn)
				pLed->BlinkingLedState = LED_STATE_OFF;
			else
				pLed->BlinkingLedState = LED_STATE_ON;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_NORMAL_INTERVAL));
		}
		break;
	default:
		break;
	}
}