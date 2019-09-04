#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct led_priv {int LedStrategy; } ;
struct TYPE_11__ {scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; struct led_priv ledpriv; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_12__ {TYPE_1__* padapter; } ;
typedef  TYPE_2__* PLED_871x ;

/* Variables and functions */
#define  SW_LED_MODE0 134 
#define  SW_LED_MODE1 133 
#define  SW_LED_MODE2 132 
#define  SW_LED_MODE3 131 
#define  SW_LED_MODE4 130 
#define  SW_LED_MODE5 129 
#define  SW_LED_MODE6 128 
 int /*<<< orphan*/  SwLedBlink (TYPE_2__*) ; 
 int /*<<< orphan*/  SwLedBlink1 (TYPE_2__*) ; 
 int /*<<< orphan*/  SwLedBlink2 (TYPE_2__*) ; 
 int /*<<< orphan*/  SwLedBlink3 (TYPE_2__*) ; 
 int /*<<< orphan*/  SwLedBlink4 (TYPE_2__*) ; 
 int /*<<< orphan*/  SwLedBlink5 (TYPE_2__*) ; 
 int /*<<< orphan*/  SwLedBlink6 (TYPE_2__*) ; 
 scalar_t__ _TRUE ; 

void BlinkHandler(PLED_871x	 pLed)
{
	struct led_priv	*ledpriv = &(pLed->padapter->ledpriv);
	_adapter		*padapter = pLed->padapter;

	//DBG_871X("%s (%s:%d)\n",__FUNCTION__, current->comm, current->pid);

	if( (padapter->bSurpriseRemoved == _TRUE) || ( padapter->bDriverStopped == _TRUE))	
	{
		//DBG_871X("%s bSurpriseRemoved:%d, bDriverStopped:%d\n", __FUNCTION__, padapter->bSurpriseRemoved, padapter->bDriverStopped);
		return;
	}

	switch(ledpriv->LedStrategy)
	{
		case SW_LED_MODE0:
			SwLedBlink(pLed);
			break;
		
		case SW_LED_MODE1:
			SwLedBlink1(pLed);
			break;
		
		case SW_LED_MODE2:
			SwLedBlink2(pLed);
			break;
			
		case SW_LED_MODE3:
			SwLedBlink3(pLed);
			break;

		case SW_LED_MODE4:
			SwLedBlink4(pLed);
			break;			

		case SW_LED_MODE5:
			SwLedBlink5(pLed);
			break;

		case SW_LED_MODE6:
			SwLedBlink6(pLed);
			break;

		default:
			//RT_TRACE(COMP_LED, DBG_LOUD, ("BlinkWorkItemCallback 0x%x \n", pHalData->LedStrategy));
			//SwLedBlink(pLed);
			break;
	}
}