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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i740fb_par {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int i740inreg (struct i740fb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_mm_w_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void i740outreg_mask(struct i740fb_par *par, u16 port, u8 reg,
				   u8 val, u8 mask)
{
	vga_mm_w_fast(par->regs, port, reg, (val & mask)
		| (i740inreg(par, port, reg) & ~mask));
}