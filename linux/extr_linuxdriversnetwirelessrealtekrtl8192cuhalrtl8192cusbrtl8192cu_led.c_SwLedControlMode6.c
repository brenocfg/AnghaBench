#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mlme_priv {int dummy; } ;
struct TYPE_7__ {void* CurrLedState; int /*<<< orphan*/  BlinkTimer; void* BlinkingLedState; } ;
struct led_priv {TYPE_2__ SwLed0; } ;
struct TYPE_6__ {struct mlme_priv mlmepriv; struct led_priv ledpriv; } ;
typedef  TYPE_1__ _adapter ;
typedef  TYPE_2__* PLED_871x ;
typedef  int LED_CTL_MODE ;

/* Variables and functions */
#define  LED_CTL_LINK 131 
#define  LED_CTL_NO_LINK 130 
#define  LED_CTL_POWER_OFF 129 
#define  LED_CTL_POWER_ON 128 
 void* RTW_LED_ON ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SwLedOff (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  _cancel_timer_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl8712_led_c_ ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SwLedControlMode6(
	_adapter				*padapter,
	LED_CTL_MODE		LedAction
)
{
	struct led_priv	*ledpriv = &(padapter->ledpriv);
	struct mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	PLED_871x pLed0 = &(ledpriv->SwLed0);
	
	switch(LedAction)
	{
		case LED_CTL_POWER_ON:
		case LED_CTL_LINK:
		case LED_CTL_NO_LINK:
			_cancel_timer_ex(&(pLed0->BlinkTimer));
			pLed0->CurrLedState = RTW_LED_ON;
			pLed0->BlinkingLedState = RTW_LED_ON;
			_set_timer(&(pLed0->BlinkTimer), 0);
			break;

		case LED_CTL_POWER_OFF:
			SwLedOff(padapter, pLed0);
			break;

		default:
			break;
	}

	RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("ledcontrol 6 Led %d\n", pLed0->CurrLedState));
}