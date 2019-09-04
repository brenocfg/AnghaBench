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
typedef  int u64 ;
typedef  int u32 ;
struct ixp46x_ts_regs {int /*<<< orphan*/  systime_hi; int /*<<< orphan*/  systime_lo; } ;

/* Variables and functions */
 int TICKS_NS_SHIFT ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixp_systime_write(struct ixp46x_ts_regs *regs, u64 ns)
{
	u32 hi, lo;

	ns >>= TICKS_NS_SHIFT;
	hi = ns >> 32;
	lo = ns & 0xffffffff;

	__raw_writel(lo, &regs->systime_lo);
	__raw_writel(hi, &regs->systime_hi);
}