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
typedef  scalar_t__ u32 ;
struct stm32_usbphyc {scalar_t__ switch_setup; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ STM32_USBPHYC_MISC ; 
 int /*<<< orphan*/  SWITHOST ; 
 int /*<<< orphan*/  stm32_usbphyc_clr_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_usbphyc_set_bits (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_usbphyc_switch_setup(struct stm32_usbphyc *usbphyc,
				       u32 utmi_switch)
{
	if (!utmi_switch)
		stm32_usbphyc_clr_bits(usbphyc->base + STM32_USBPHYC_MISC,
				       SWITHOST);
	else
		stm32_usbphyc_set_bits(usbphyc->base + STM32_USBPHYC_MISC,
				       SWITHOST);
	usbphyc->switch_setup = utmi_switch;
}