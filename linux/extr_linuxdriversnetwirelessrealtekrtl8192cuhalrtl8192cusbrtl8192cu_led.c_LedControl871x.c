#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct led_priv {scalar_t__ bRegUseLed; int LedStrategy; } ;
struct TYPE_10__ {scalar_t__ rf_pwrstate; scalar_t__ rfoff_reason; } ;
struct TYPE_11__ {scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; scalar_t__ hw_init_completed; TYPE_1__ pwrctrlpriv; struct led_priv ledpriv; } ;
typedef  TYPE_2__ _adapter ;
typedef  int /*<<< orphan*/  LED_CTL_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CTL_LINK ; 
 int /*<<< orphan*/  LED_CTL_NO_LINK ; 
 int /*<<< orphan*/  LED_CTL_POWER_ON ; 
 int /*<<< orphan*/  LED_CTL_RX ; 
 int /*<<< orphan*/  LED_CTL_SITE_SURVEY ; 
 int /*<<< orphan*/  LED_CTL_TX ; 
 scalar_t__ RF_CHANGE_BY_PS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
#define  SW_LED_MODE0 134 
#define  SW_LED_MODE1 133 
#define  SW_LED_MODE2 132 
#define  SW_LED_MODE3 131 
#define  SW_LED_MODE4 130 
#define  SW_LED_MODE5 129 
#define  SW_LED_MODE6 128 
 int /*<<< orphan*/  SwLedControlMode1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SwLedControlMode2 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SwLedControlMode3 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SwLedControlMode4 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SwLedControlMode5 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SwLedControlMode6 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _FALSE ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl8712_led_c_ ; 
 scalar_t__ rf_on ; 

__attribute__((used)) static void
LedControl871x(
	_adapter				*padapter,
	LED_CTL_MODE		LedAction
	)
{
	struct led_priv	*ledpriv = &(padapter->ledpriv);

       if( (padapter->bSurpriseRemoved == _TRUE) || ( padapter->bDriverStopped == _TRUE) 
	   	||(padapter->hw_init_completed == _FALSE) )	
       {
             return;
       }


	if( ledpriv->bRegUseLed == _FALSE)
		return;

	//if (!priv->up)
	//	return;

	//if(priv->bInHctTest)
	//	return;

	if( (padapter->pwrctrlpriv.rf_pwrstate != rf_on &&
		padapter->pwrctrlpriv.rfoff_reason > RF_CHANGE_BY_PS) &&
		(LedAction == LED_CTL_TX || LedAction == LED_CTL_RX || 
		 LedAction == LED_CTL_SITE_SURVEY || 
		 LedAction == LED_CTL_LINK || 
		 LedAction == LED_CTL_NO_LINK ||
		 LedAction == LED_CTL_POWER_ON) )
	{
		return;
	}
	
	switch(ledpriv->LedStrategy)
	{
		case SW_LED_MODE0:
			//SwLedControlMode0(padapter, LedAction);
			break;

		case SW_LED_MODE1:
			SwLedControlMode1(padapter, LedAction);
			break;
		case SW_LED_MODE2:
			SwLedControlMode2(padapter, LedAction);
                	break;

		case SW_LED_MODE3:
			SwLedControlMode3(padapter, LedAction);
			break;	

		case SW_LED_MODE4:
			SwLedControlMode4(padapter, LedAction);
			break;			

		case SW_LED_MODE5:
			SwLedControlMode5(padapter, LedAction);
			break;

		case SW_LED_MODE6:
			SwLedControlMode6(padapter, LedAction);
			break;

		default:
			break;
	}
	
	RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("LedStrategy:%d, LedAction %d\n", ledpriv->LedStrategy,LedAction));
}