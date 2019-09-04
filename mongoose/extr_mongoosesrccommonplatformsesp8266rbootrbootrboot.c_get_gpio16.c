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
typedef  int uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  PAD_XPD_DCDC_CONF ; 
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_GPIO_CONF ; 
 int /*<<< orphan*/  RTC_GPIO_ENABLE ; 
 int /*<<< orphan*/  RTC_GPIO_IN_DATA ; 
 int /*<<< orphan*/  RTC_GPIO_OUT ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32 get_gpio16(void) {
	// set output level to 1
	WRITE_PERI_REG(RTC_GPIO_OUT, (READ_PERI_REG(RTC_GPIO_OUT) & (uint32)0xfffffffe) | (uint32)(1));

	// read level
	WRITE_PERI_REG(PAD_XPD_DCDC_CONF, (READ_PERI_REG(PAD_XPD_DCDC_CONF) & 0xffffffbc) | (uint32)0x1);	// mux configuration for XPD_DCDC and rtc_gpio0 connection
	WRITE_PERI_REG(RTC_GPIO_CONF, (READ_PERI_REG(RTC_GPIO_CONF) & (uint32)0xfffffffe) | (uint32)0x0);	//mux configuration for out enable
	WRITE_PERI_REG(RTC_GPIO_ENABLE, READ_PERI_REG(RTC_GPIO_ENABLE) & (uint32)0xfffffffe);	//out disable

	uint32 x = (READ_PERI_REG(RTC_GPIO_IN_DATA) & 1);

	return x;
}