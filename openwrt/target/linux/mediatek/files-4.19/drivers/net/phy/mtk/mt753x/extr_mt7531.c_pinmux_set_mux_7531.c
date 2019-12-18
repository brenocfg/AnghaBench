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
struct gsw_mt753x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_MODE_REGS (int) ; 
 int GPIO_MODE_S ; 
 int mt753x_reg_read (struct gsw_mt753x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt753x_reg_write (struct gsw_mt753x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pinmux_set_mux_7531(struct gsw_mt753x *gsw, u32 pin, u32 mode)
{
	u32 val;

	val = mt753x_reg_read(gsw, GPIO_MODE_REGS(pin));
	val &= ~(0xf << (pin & 7) * GPIO_MODE_S);
	val |= mode << (pin & 7) * GPIO_MODE_S;
	mt753x_reg_write(gsw, GPIO_MODE_REGS(pin), val);
}