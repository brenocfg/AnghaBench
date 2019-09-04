#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct led_priv {int /*<<< orphan*/  SwLed1; int /*<<< orphan*/  SwLed0; int /*<<< orphan*/  LedControlHandler; } ;
struct TYPE_4__ {struct led_priv ledpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  InitLed871x (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_PIN_LED0 ; 
 int /*<<< orphan*/  LED_PIN_LED1 ; 
 int /*<<< orphan*/  LedControl871x ; 

void
rtl8192cu_InitSwLeds(
	_adapter	*padapter
	)
{
	struct led_priv *pledpriv = &(padapter->ledpriv);

	pledpriv->LedControlHandler = LedControl871x;

	InitLed871x(padapter, &(pledpriv->SwLed0), LED_PIN_LED0);

	InitLed871x(padapter,&(pledpriv->SwLed1), LED_PIN_LED1);
}