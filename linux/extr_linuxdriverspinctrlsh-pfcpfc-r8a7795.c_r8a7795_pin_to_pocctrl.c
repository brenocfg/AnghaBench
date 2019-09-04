#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sh_pfc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t POCCTRL ; 
 unsigned int RCAR_GP_PIN (int,int) ; 
 TYPE_1__* pinmux_ioctrl_regs ; 

__attribute__((used)) static int r8a7795_pin_to_pocctrl(struct sh_pfc *pfc, unsigned int pin, u32 *pocctrl)
{
	int bit = -EINVAL;

	*pocctrl = pinmux_ioctrl_regs[POCCTRL].reg;

	if (pin >= RCAR_GP_PIN(3, 0) && pin <= RCAR_GP_PIN(3, 11))
		bit = pin & 0x1f;

	if (pin >= RCAR_GP_PIN(4, 0) && pin <= RCAR_GP_PIN(4, 17))
		bit = (pin & 0x1f) + 12;

	return bit;
}