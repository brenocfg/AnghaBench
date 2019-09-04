#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct mlme_priv {int dummy; } ;
struct TYPE_15__ {scalar_t__ BlinkingLedState; int CurrLedState; int /*<<< orphan*/  BlinkTimer; scalar_t__ bLedWPSBlinkInProgress; scalar_t__ bLedOn; scalar_t__ bLedLinkBlinkInProgress; scalar_t__ bLedBlinkInProgress; int /*<<< orphan*/  BlinkTimes; scalar_t__ bLedNoLinkBlinkInProgress; scalar_t__ bLedScanBlinkInProgress; scalar_t__ bSWLedCtrl; TYPE_2__* padapter; } ;
struct led_priv {TYPE_3__ SwLed1; } ;
struct TYPE_13__ {scalar_t__ rf_pwrstate; } ;
struct TYPE_14__ {TYPE_1__ pwrctrlpriv; struct mlme_priv mlmepriv; struct led_priv ledpriv; } ;
typedef  TYPE_2__ _adapter ;
struct TYPE_16__ {scalar_t__ EEPROMCustomerID; } ;
typedef  TYPE_3__* PLED_871x ;
typedef  TYPE_4__ HAL_DATA_TYPE ;

/* Variables and functions */
 TYPE_4__* GET_HAL_DATA (TYPE_2__*) ; 
 int /*<<< orphan*/  LED_BLINK_FASTER_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_LINK_INTERVAL_ALPHA ; 
#define  LED_BLINK_NORMAL 133 
 int /*<<< orphan*/  LED_BLINK_NO_LINK_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_SCAN_INTERVAL_ALPHA ; 
#define  LED_BLINK_SLOWLY 132 
#define  LED_BLINK_WPS 131 
#define  LED_BLINK_WPS_STOP 130 
 int /*<<< orphan*/  LED_BLINK_WPS_SUCESS_INTERVAL_ALPHA ; 
#define  LED_SCAN_BLINK 129 
#define  LED_TXRX_BLINK 128 
 void* RTW_LED_OFF ; 
 scalar_t__ RTW_LED_ON ; 
 scalar_t__ RT_CID_819x_CAMEO ; 
 scalar_t__ RT_CID_DEFAULT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ResetLedStatus (TYPE_3__*) ; 
 int /*<<< orphan*/  SwLedOff (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  SwLedOn (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ _FALSE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl8712_led_c_ ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ rf_on ; 

__attribute__((used)) static void
SwLedBlink1(
	PLED_871x			pLed
	)
{
	_adapter				*padapter = pLed->padapter;
	HAL_DATA_TYPE		*pHalData = GET_HAL_DATA(padapter);
	struct led_priv		*ledpriv = &(padapter->ledpriv);
	struct mlme_priv		*pmlmepriv = &(padapter->mlmepriv);
	PLED_871x 			pLed1 = &(ledpriv->SwLed1);	
	u8					bStopBlinking = _FALSE;

	if(pHalData->EEPROMCustomerID == RT_CID_819x_CAMEO)
		pLed = &(ledpriv->SwLed1);	

	// Change LED according to BlinkingLedState specified.
	if( pLed->BlinkingLedState == RTW_LED_ON ) 
	{
		SwLedOn(padapter, pLed);
		RT_TRACE(_module_rtl8712_led_c_,_drv_info_,( "Blinktimes (%d): turn on\n", pLed->BlinkTimes));
	}
	else 
	{
		SwLedOff(padapter, pLed);
		RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("Blinktimes (%d): turn off\n", pLed->BlinkTimes));
	}


	if(pHalData->EEPROMCustomerID == RT_CID_DEFAULT)
	{
		if(check_fwstate(pmlmepriv, _FW_LINKED)== _TRUE)
		{
			if(!pLed1->bSWLedCtrl)
			{
				SwLedOn(padapter, pLed1); 	
				pLed1->bSWLedCtrl = _TRUE;
			}
			else if(!pLed1->bLedOn)	
				SwLedOn(padapter, pLed1);
			RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("Blinktimes (): turn on pLed1\n"));
		}
		else 
		{
			if(!pLed1->bSWLedCtrl)
			{
				SwLedOff(padapter, pLed1);
				pLed1->bSWLedCtrl = _TRUE;
			}
			else if(pLed1->bLedOn)
				SwLedOff(padapter, pLed1);
			RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("Blinktimes (): turn off pLed1\n"));		
		}
	}


	if( padapter->pwrctrlpriv.rf_pwrstate != rf_on )
	{
		SwLedOff(padapter, pLed);
		ResetLedStatus(pLed);
		return;
	}
				

	switch(pLed->CurrLedState)
	{
		case LED_BLINK_SLOWLY:			
			if( pLed->bLedOn )
				pLed->BlinkingLedState = RTW_LED_OFF; 
			else
				pLed->BlinkingLedState = RTW_LED_ON;
			_set_timer(&(pLed->BlinkTimer), LED_BLINK_NO_LINK_INTERVAL_ALPHA);
			break;

		case LED_BLINK_NORMAL:
			if( pLed->bLedOn )
				pLed->BlinkingLedState = RTW_LED_OFF; 
			else
				pLed->BlinkingLedState = RTW_LED_ON;
			_set_timer(&(pLed->BlinkTimer), LED_BLINK_LINK_INTERVAL_ALPHA);
			break;
			
		case LED_SCAN_BLINK:
			pLed->BlinkTimes--;
			if( pLed->BlinkTimes == 0 )
			{
				bStopBlinking = _TRUE;
			}
			
			if(bStopBlinking)
			{
				if(check_fwstate(pmlmepriv, _FW_LINKED)== _TRUE)
				{
					pLed->bLedLinkBlinkInProgress = _TRUE;
					pLed->CurrLedState = LED_BLINK_NORMAL;
					if( pLed->bLedOn )
						pLed->BlinkingLedState = RTW_LED_OFF; 
					else
						pLed->BlinkingLedState = RTW_LED_ON;
					_set_timer(&(pLed->BlinkTimer), LED_BLINK_LINK_INTERVAL_ALPHA);
					RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("CurrLedState %d\n", pLed->CurrLedState));
					
				}
				else if(check_fwstate(pmlmepriv, _FW_LINKED)== _FALSE)
				{
					pLed->bLedNoLinkBlinkInProgress = _TRUE;
					pLed->CurrLedState = LED_BLINK_SLOWLY;
					if( pLed->bLedOn )
						pLed->BlinkingLedState = RTW_LED_OFF; 
					else
						pLed->BlinkingLedState = RTW_LED_ON;
					_set_timer(&(pLed->BlinkTimer), LED_BLINK_NO_LINK_INTERVAL_ALPHA);
					RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("CurrLedState %d\n", pLed->CurrLedState));					
				}
				pLed->bLedScanBlinkInProgress = _FALSE;
			}
			else
			{
				if( pLed->bLedOn )
					pLed->BlinkingLedState = RTW_LED_OFF;
				else
					pLed->BlinkingLedState = RTW_LED_ON;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_SCAN_INTERVAL_ALPHA);
			}
			break;

		case LED_TXRX_BLINK:
			pLed->BlinkTimes--;
			if( pLed->BlinkTimes == 0 )
			{
				bStopBlinking = _TRUE;
			}
			if(bStopBlinking)
			{
				if(check_fwstate(pmlmepriv, _FW_LINKED)== _TRUE)
				{
					pLed->bLedLinkBlinkInProgress = _TRUE;
					pLed->CurrLedState = LED_BLINK_NORMAL;
					if( pLed->bLedOn )
						pLed->BlinkingLedState = RTW_LED_OFF;
					else
						pLed->BlinkingLedState = RTW_LED_ON;
					_set_timer(&(pLed->BlinkTimer), LED_BLINK_LINK_INTERVAL_ALPHA);
					RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("CurrLedState %d\n", pLed->CurrLedState));					
				}
				else if(check_fwstate(pmlmepriv, _FW_LINKED)== _FALSE)
				{
					pLed->bLedNoLinkBlinkInProgress = _TRUE;
					pLed->CurrLedState = LED_BLINK_SLOWLY;
					if( pLed->bLedOn )
						pLed->BlinkingLedState = RTW_LED_OFF; 
					else
						pLed->BlinkingLedState = RTW_LED_ON;
					_set_timer(&(pLed->BlinkTimer), LED_BLINK_NO_LINK_INTERVAL_ALPHA);
					RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("CurrLedState %d\n", pLed->CurrLedState));					
				}
				pLed->BlinkTimes = 0;
				pLed->bLedBlinkInProgress = _FALSE;	
			}
			else
			{
				if( pLed->bLedOn )
					pLed->BlinkingLedState = RTW_LED_OFF; 
				else
					pLed->BlinkingLedState = RTW_LED_ON;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_FASTER_INTERVAL_ALPHA);
			}
			break;

		case LED_BLINK_WPS:
			if( pLed->bLedOn )
				pLed->BlinkingLedState = RTW_LED_OFF; 
			else
				pLed->BlinkingLedState = RTW_LED_ON;
			_set_timer(&(pLed->BlinkTimer), LED_BLINK_SCAN_INTERVAL_ALPHA);
			break;

		case LED_BLINK_WPS_STOP:	//WPS success
			if(pLed->BlinkingLedState == RTW_LED_ON)
				bStopBlinking = _FALSE;
			else
				bStopBlinking = _TRUE;				

			if(bStopBlinking)
			{
				pLed->bLedLinkBlinkInProgress = _TRUE;
				pLed->CurrLedState = LED_BLINK_NORMAL;
				if( pLed->bLedOn )
					pLed->BlinkingLedState = RTW_LED_OFF; 
				else
					pLed->BlinkingLedState = RTW_LED_ON;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_LINK_INTERVAL_ALPHA);
				RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("CurrLedState %d\n", pLed->CurrLedState));
					
				pLed->bLedWPSBlinkInProgress = _FALSE;	
			}
			else
			{
				pLed->BlinkingLedState = RTW_LED_OFF;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_WPS_SUCESS_INTERVAL_ALPHA);
			}
			break;
					
		default:
			break;
	}

}