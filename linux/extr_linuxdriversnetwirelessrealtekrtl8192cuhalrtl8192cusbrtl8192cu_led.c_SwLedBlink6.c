#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mlme_priv {int dummy; } ;
struct TYPE_8__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_9__ {scalar_t__ BlinkingLedState; int /*<<< orphan*/  BlinkTimes; TYPE_1__* padapter; } ;
typedef  TYPE_2__* PLED_871x ;

/* Variables and functions */
 scalar_t__ RTW_LED_ON ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SwLedOff (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SwLedOn (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl8712_led_c_ ; 

__attribute__((used)) static void
SwLedBlink6(
	PLED_871x			pLed
	)
{
	_adapter			*padapter = pLed->padapter;
	struct mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	u8				bStopBlinking = _FALSE;

	// Change LED according to BlinkingLedState specified.
	if( pLed->BlinkingLedState == RTW_LED_ON ) 
	{
		SwLedOn(padapter, pLed);
		RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("Blinktimes (%d): turn on\n", pLed->BlinkTimes));
	}
	else 
	{
		SwLedOff(padapter, pLed);
		RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("Blinktimes (%d): turn off\n", pLed->BlinkTimes));
	}

	RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("<==== blink6\n"));
}