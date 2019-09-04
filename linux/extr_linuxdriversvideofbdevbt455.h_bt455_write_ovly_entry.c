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
typedef  int /*<<< orphan*/  u8 ;
struct bt455_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt455_reset_reg (struct bt455_regs*) ; 
 int /*<<< orphan*/  bt455_write_ovly_next (struct bt455_regs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bt455_write_ovly_entry(struct bt455_regs *regs, u8 grey)
{
	bt455_reset_reg(regs);
	bt455_write_ovly_next(regs, grey);
}