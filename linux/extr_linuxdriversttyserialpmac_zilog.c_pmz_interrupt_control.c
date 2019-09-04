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
struct uart_pmac_port {int* curregs; } ;

/* Variables and functions */
 int EXT_INT_ENAB ; 
 int INT_ALL_Rx ; 
 int /*<<< orphan*/  R1 ; 
 int RxINT_MASK ; 
 int TxINT_ENAB ; 
 int /*<<< orphan*/  ZS_IS_EXTCLK (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  write_zsreg (struct uart_pmac_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pmz_interrupt_control(struct uart_pmac_port *uap, int enable)
{
	if (enable) {
		uap->curregs[1] |= INT_ALL_Rx | TxINT_ENAB;
		if (!ZS_IS_EXTCLK(uap))
			uap->curregs[1] |= EXT_INT_ENAB;
	} else {
		uap->curregs[1] &= ~(EXT_INT_ENAB | TxINT_ENAB | RxINT_MASK);
	}
	write_zsreg(uap, R1, uap->curregs[1]);
}