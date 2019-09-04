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
struct uart_pmac_port {int dummy; } ;

/* Variables and functions */
 int BRENAB ; 
 int BRSRC ; 
 int CHRA ; 
 int CHRB ; 
 int ERR_RES ; 
 int LOOPBAK ; 
 int MONSYNC ; 
 int NV ; 
 int RCBR ; 
 int RES_EXT_INT ; 
 int RTS ; 
 int Rx8 ; 
 int RxENABLE ; 
 int Rx_CH_AV ; 
 int SB_MASK ; 
 int TCBR ; 
 int Tx8 ; 
 int X16CLK ; 
 int X1CLK ; 
 scalar_t__ ZS_IS_CHANNEL_A (struct uart_pmac_port*) ; 
 int read_zsreg (struct uart_pmac_port*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_zsreg (struct uart_pmac_port*,int,int) ; 
 int /*<<< orphan*/  zssync (struct uart_pmac_port*) ; 

__attribute__((used)) static void pmz_fix_zero_bug_scc(struct uart_pmac_port *uap)
{
	write_zsreg(uap, 9, ZS_IS_CHANNEL_A(uap) ? CHRA : CHRB);
	zssync(uap);
	udelay(10);
	write_zsreg(uap, 9, (ZS_IS_CHANNEL_A(uap) ? CHRA : CHRB) | NV);
	zssync(uap);

	write_zsreg(uap, 4, X1CLK | MONSYNC);
	write_zsreg(uap, 3, Rx8);
	write_zsreg(uap, 5, Tx8 | RTS);
	write_zsreg(uap, 9, NV);	/* Didn't we already do this? */
	write_zsreg(uap, 11, RCBR | TCBR);
	write_zsreg(uap, 12, 0);
	write_zsreg(uap, 13, 0);
	write_zsreg(uap, 14, (LOOPBAK | BRSRC));
	write_zsreg(uap, 14, (LOOPBAK | BRSRC | BRENAB));
	write_zsreg(uap, 3, Rx8 | RxENABLE);
	write_zsreg(uap, 0, RES_EXT_INT);
	write_zsreg(uap, 0, RES_EXT_INT);
	write_zsreg(uap, 0, RES_EXT_INT);	/* to kill some time */

	/* The channel should be OK now, but it is probably receiving
	 * loopback garbage.
	 * Switch to asynchronous mode, disable the receiver,
	 * and discard everything in the receive buffer.
	 */
	write_zsreg(uap, 9, NV);
	write_zsreg(uap, 4, X16CLK | SB_MASK);
	write_zsreg(uap, 3, Rx8);

	while (read_zsreg(uap, 0) & Rx_CH_AV) {
		(void)read_zsreg(uap, 8);
		write_zsreg(uap, 0, RES_EXT_INT);
		write_zsreg(uap, 0, ERR_RES);
	}
}