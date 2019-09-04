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
struct mlme_priv {int dummy; } ;
struct _adapter {struct mlme_priv mlmepriv; } ;
struct LED_871x {scalar_t__ BlinkingLedState; int CurrLedState; int bLedScanBlinkInProgress; int bLedBlinkInProgress; int bLedWPSBlinkInProgress; int /*<<< orphan*/  BlinkTimer; int /*<<< orphan*/  bLedOn; int /*<<< orphan*/  BlinkTimes; struct _adapter* padapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_BLINK_FASTER_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_SCAN_INTERVAL_ALPHA ; 
#define  LED_BLINK_WPS 131 
#define  LED_BLINK_WPS_STOP 130 
 int /*<<< orphan*/  LED_BLINK_WPS_SUCCESS_INTERVAL_ALPHA ; 
#define  LED_SCAN_BLINK 129 
 void* LED_STATE_OFF ; 
 scalar_t__ LED_STATE_ON ; 
#define  LED_TXRX_BLINK 128 
 int /*<<< orphan*/  SwLedOff (struct _adapter*,struct LED_871x*) ; 
 int /*<<< orphan*/  SwLedOn (struct _adapter*,struct LED_871x*) ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SwLedBlink3(struct LED_871x *pLed)
{
	struct _adapter *padapter = pLed->padapter;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	u8 bStopBlinking = false;

	/* Change LED according to BlinkingLedState specified. */
	if (pLed->BlinkingLedState == LED_STATE_ON)
		SwLedOn(padapter, pLed);
	else
		if (pLed->CurrLedState != LED_BLINK_WPS_STOP)
			SwLedOff(padapter, pLed);
	switch (pLed->CurrLedState) {
	case LED_SCAN_BLINK:
		pLed->BlinkTimes--;
		if (pLed->BlinkTimes == 0)
			bStopBlinking = true;
		if (bStopBlinking) {
			if (check_fwstate(pmlmepriv, _FW_LINKED)) {
				pLed->CurrLedState = LED_STATE_ON;
				pLed->BlinkingLedState = LED_STATE_ON;
				if (!pLed->bLedOn)
					SwLedOn(padapter, pLed);
			} else if (!check_fwstate(pmlmepriv, _FW_LINKED)) {
				pLed->CurrLedState = LED_STATE_OFF;
				pLed->BlinkingLedState = LED_STATE_OFF;
				if (pLed->bLedOn)
					SwLedOff(padapter, pLed);
			}
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
			if (check_fwstate(pmlmepriv, _FW_LINKED)) {
				pLed->CurrLedState = LED_STATE_ON;
				pLed->BlinkingLedState = LED_STATE_ON;
				if (!pLed->bLedOn)
					SwLedOn(padapter, pLed);
			} else if (!check_fwstate(pmlmepriv, _FW_LINKED)) {
				pLed->CurrLedState = LED_STATE_OFF;
				pLed->BlinkingLedState = LED_STATE_OFF;
				if (pLed->bLedOn)
					SwLedOff(padapter, pLed);
			}
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
		if (pLed->bLedOn)
			pLed->BlinkingLedState = LED_STATE_OFF;
		else
			pLed->BlinkingLedState = LED_STATE_ON;
		mod_timer(&pLed->BlinkTimer, jiffies +
			  msecs_to_jiffies(LED_BLINK_SCAN_INTERVAL_ALPHA));
		break;
	case LED_BLINK_WPS_STOP:	/*WPS success*/
		if (pLed->BlinkingLedState == LED_STATE_ON) {
			pLed->BlinkingLedState = LED_STATE_OFF;
			mod_timer(&pLed->BlinkTimer, jiffies +
				  msecs_to_jiffies(LED_BLINK_WPS_SUCCESS_INTERVAL_ALPHA));
			bStopBlinking = false;
		} else {
			bStopBlinking = true;
		}
		if (bStopBlinking) {
			pLed->CurrLedState = LED_STATE_ON;
			pLed->BlinkingLedState = LED_STATE_ON;
			SwLedOn(padapter, pLed);
			pLed->bLedWPSBlinkInProgress = false;
		}
		break;
	default:
		break;
	}
}