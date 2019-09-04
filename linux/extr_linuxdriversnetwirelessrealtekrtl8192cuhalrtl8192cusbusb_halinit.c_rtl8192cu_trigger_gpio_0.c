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
typedef  int u32 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_8192C (char*) ; 
 int /*<<< orphan*/  GPIO_DEBUG_PORT_NUM ; 
 scalar_t__ REG_GPIO_PIN_CTRL ; 
 int /*<<< orphan*/  rtw_write16_async (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32_async (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  rtw_write8_async (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void rtl8192cu_trigger_gpio_0(_adapter *padapter)
{

	u32 gpioctrl;
	DBG_8192C("==> trigger_gpio_0...\n");
	rtw_write16_async(padapter,REG_GPIO_PIN_CTRL,0);
	rtw_write8_async(padapter,REG_GPIO_PIN_CTRL+2,0xFF);
	gpioctrl = (BIT(GPIO_DEBUG_PORT_NUM)<<24 )|(BIT(GPIO_DEBUG_PORT_NUM)<<16);
	rtw_write32_async(padapter,REG_GPIO_PIN_CTRL,gpioctrl);
	gpioctrl |= (BIT(GPIO_DEBUG_PORT_NUM)<<8);
	rtw_write32_async(padapter,REG_GPIO_PIN_CTRL,gpioctrl);
	DBG_8192C("<=== trigger_gpio_0...\n");

}