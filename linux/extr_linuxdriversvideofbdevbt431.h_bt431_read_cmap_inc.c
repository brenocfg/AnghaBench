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
typedef  int /*<<< orphan*/  volatile u16 ;
struct bt431_regs {int /*<<< orphan*/  volatile addr_cmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline u16 bt431_read_cmap_inc(struct bt431_regs *regs)
{
	/*
	 * The compiler splits the write in two bytes without the
	 * helper variable.
	 */
	volatile u16 *r = &(regs->addr_cmap);

	mb();
	return *r;
}