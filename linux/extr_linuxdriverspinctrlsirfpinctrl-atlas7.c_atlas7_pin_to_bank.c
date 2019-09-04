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

/* Variables and functions */
 scalar_t__ ATLAS7_PINCTRL_BANK_0_PINS ; 

__attribute__((used)) static inline u32 atlas7_pin_to_bank(u32 pin)
{
	return (pin >= ATLAS7_PINCTRL_BANK_0_PINS) ? 1 : 0;
}